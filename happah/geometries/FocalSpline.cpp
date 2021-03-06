#include "happah/geometries/FocalSpline.h"
#include "happah/HappahUtils.h"
#include "happah/HappahConstants.h"
#include <iostream>
#define RADIUS 1.0f

using namespace std;



FocalSpline::FocalSpline()
	: m_center(hpvec3(0.0f,0.0f,0.0f)),m_detail(20),m_phi(0),m_doLaneRiesenfeld(false),m_LRIterations(0),m_LRDegree(0),m_showControlPolygon(true),m_doBSpline(true),m_showCircle(true) {
	m_controlPoints = new vector<vector<hpvec3>*>;
	m_generatedSpline = new vector<hpvec3>;
	m_BSplineKnots = new vector<hpreal>;
	m_BSplineControlPoints = new vector<hpvec3>;
	m_BSplineKnots->push_back(M_PI/4.0f);
	m_BSplineKnots->push_back(M_PI/4.0f);
	m_BSplineKnots->push_back(M_PI/4.0f);
	m_BSplineKnots->push_back(M_PI/4.0f);
	m_BSplineKnots->push_back(3*M_PI/4.0f);
	m_BSplineKnots->push_back(3*M_PI/4.0f);
	m_BSplineKnots->push_back(3*M_PI/4.0f);
	m_BSplineKnots->push_back(3*M_PI/4.0f);
	m_BSplineControlPoints->push_back(hpvec3(M_PI/4.0f,0,2.0f));
	m_BSplineControlPoints->push_back(hpvec3((M_PI/4.0f)+(0.33f*M_PI/2.0f),0,2.0f));
	m_BSplineControlPoints->push_back(hpvec3((M_PI/4.0f)+(0.66f*M_PI/2.0f),0,2.0f));
	m_BSplineControlPoints->push_back(hpvec3(3*M_PI/4.0f,0,2.0f));
	m_focalBSplineCurve = new FocalBSplineCurve(m_BSplineKnots,m_BSplineControlPoints);
//	m_focalBSplineCurve->insertKnot(M_PI/2.0f);
}

FocalSpline::~FocalSpline() {

}

void FocalSpline::setControlPoint(hpuint index, hpvec3 controlPoint){
	int bezierCurveIndex = calculateFocalBezierCurveIndexFromPointIndex(index);
	int currentIndex = calculatePointIndexFromBezierIndex(bezierCurveIndex, index);
	m_controlPoints->at(bezierCurveIndex)->at(currentIndex)=HPUtils::cartesianToPolarCoordinates(controlPoint);
	adjustControlPoints(bezierCurveIndex,currentIndex);
	update();
}

hpvec3 FocalSpline::getControlPoint(hpuint index){
	int bezierCurveIndex = calculateFocalBezierCurveIndexFromPointIndex(index);
	int currentIndex = calculatePointIndexFromBezierIndex(bezierCurveIndex, index);
	return HPUtils::polarToCartesianCoordinates(m_controlPoints->at(bezierCurveIndex)->at(currentIndex));
}

void FocalSpline::init(int degree){
	m_controlPoints->push_back(new vector<hpvec3>);
	hpreal radius = 3.0f;

	if (degree  <1){
		m_focalBezierCurves.push_back(new FocalBezierCurve(m_phi,m_controlPoints->at(0)));
		update();
		return;
	}
	else
	{

			m_phi = (M_PI/(float)(degree))/2.0f;
		for (int i = 0; i <= degree ; i++){
			hpvec3 controlPoint = hpvec3(i*m_phi,0.0f,radius);
			m_controlPoints->at(0)->push_back(controlPoint);
		}
		if (m_controlPoints->at(0)->size() > 0){
			m_focalBezierCurves.push_back(new FocalBezierCurve(m_phi,m_controlPoints->at(0)));
			update();
		}
	}
}


void FocalSpline::addControlPoint(int selectionIndex){
	int bezierCurveIndex = 0;
	if (selectionIndex >=0){
		bezierCurveIndex = calculateFocalBezierCurveIndexFromPointIndex(selectionIndex);
	}
	hpvec3 newPoint;
	hpreal newPhi;
	hpreal newRadius;

	if (m_controlPoints->at(bezierCurveIndex)->size()<1){
		newPhi = M_PI/4.0f;
		newRadius = RADIUS*3;
		m_phi = newPhi;

	}
	else{
	newPhi= m_controlPoints->at(bezierCurveIndex)->back().x + m_phi;
	if  (newPhi == 0){
		newPhi = M_PI/4.0f;
		m_phi = newPhi;
	}
	newRadius = m_controlPoints->at(bezierCurveIndex)->back().z;
	if (newRadius == 0)
		newRadius== RADIUS*3;
	}

	newPoint = hpvec3(newPhi,0,newRadius);
	m_controlPoints->at(bezierCurveIndex)->push_back(newPoint);
	if (m_controlPoints->at(bezierCurveIndex)->size() > 1){
	adjustControlPoints(bezierCurveIndex,m_controlPoints->at(bezierCurveIndex)->size()-1);
	}
	m_focalBezierCurves.at(bezierCurveIndex)->update(m_phi,m_controlPoints->at(bezierCurveIndex));
	update();
}

void FocalSpline::addControlPoint(hpvec3 point){

	hpvec3 newPoint = HPUtils::cartesianToPolarCoordinates(point);
	int insertionIndex;

	for(hpuint j = 0; j < m_controlPoints->size(); j++){
	for(hpuint i = 0; i < m_controlPoints->at(j)->size(); i++){
		if (newPoint.x < m_controlPoints->at(j)->at(i).x){
			m_controlPoints->at(j)->insert(m_controlPoints->at(j)->begin()+i,newPoint);
			adjustControlPoints(j,i);
			insertionIndex = j;
			break;
		}
	}
	}
	if (newPoint.x > m_controlPoints->back()->back().x){
		m_controlPoints->back()->push_back(newPoint);
		insertionIndex = m_controlPoints->size()-1;
		adjustControlPoints(insertionIndex,m_controlPoints->back()->size()-1);
	}
	m_focalBezierCurves.at(insertionIndex)->update(m_phi,m_controlPoints->at(insertionIndex));
	update();

}

void FocalSpline::update(){
	m_generatedSpline->clear();
	if(m_doLaneRiesenfeld==false){
		for(int i = 0; i<m_focalBezierCurves.size();i++){
			generateFocalSpline(i);
		}
	}
	else{
		generateLaneRiesenfeld(m_LRDegree,m_LRIterations);
	}

}

void FocalSpline::generateFocalSpline(int index){

	if (m_controlPoints->at(index)->size() <1){
		return;
	}
	hpreal delta = 0.0f;
	for(int i = 0 ; i < m_detail;i++){
		delta = i* 1.0f/((hpreal)m_detail-1.0f);
		m_generatedSpline->push_back(m_focalBezierCurves.at(index)->evaluate(delta));
	}
}





void FocalSpline::adjustControlPoints(int bezierCurveIndex,int currentIndex,int direction){
	int updateTo = direction;
	hpreal phi;
	if(bezierCurveIndex != 0 && currentIndex != 0 && m_controlPoints->at(bezierCurveIndex)->at(currentIndex).x <= m_controlPoints->at(0)->at(1).x)
		m_controlPoints->at(bezierCurveIndex)->at(currentIndex).x += 2*M_PI;

	if (currentIndex == 0)
		phi = m_controlPoints->at(bezierCurveIndex)->at(currentIndex+1).x - m_controlPoints->at(bezierCurveIndex)->at(currentIndex).x;
	else
		phi = m_controlPoints->at(bezierCurveIndex)->at(currentIndex).x - m_controlPoints->at(bezierCurveIndex)->at(currentIndex-1).x;
	if (phi < 0)
		phi = 0.0f;

	if (phi >= M_PI)
		phi = M_PI - HP_EPSILON;
	for(int i= 0; i < m_controlPoints->at(bezierCurveIndex)->size(); i++){
	
		hpreal phiPoint = m_controlPoints->at(bezierCurveIndex)->at(currentIndex).x;
		hpreal newPhi = 0.0f;
		newPhi=phiPoint+(i-currentIndex)*phi;
		m_controlPoints->at(bezierCurveIndex)->at(i).x = newPhi;
	}
	if(bezierCurveIndex < m_controlPoints->size()-1 &&(updateTo == 0 || updateTo == 1)){
		m_controlPoints->at(bezierCurveIndex+1)->at(0) = m_controlPoints->at(bezierCurveIndex)->back();
		adjustControlPoints(bezierCurveIndex+1,0,1);
	}
	if (bezierCurveIndex > 0 && (updateTo == 0 || updateTo == 2)){
		m_controlPoints->at(bezierCurveIndex-1)->back()=m_controlPoints->at(bezierCurveIndex)->at(0);
		adjustControlPoints(bezierCurveIndex-1,m_controlPoints->at(bezierCurveIndex-1)->size()-1,2);
	}

}

LineMesh3D* FocalSpline::toLineMesh(){
	std::vector<hpvec3>* verticesAndNormals = new std::vector<hpvec3>;
	std::vector<hpuint>* indices = new std::vector<hpuint>;

	//draw controlpolygon
	int i = 0;
	if(m_showControlPolygon && !m_doBSpline){
	for(vector<vector<hpvec3>*>::iterator iter=m_controlPoints->begin();iter !=m_controlPoints->end();++iter){
		if ((*iter)->size()>0){
		for(vector<hpvec3>::iterator it = (*iter)->begin(); it != (*iter)->end(); ++it){
				hpvec3 vertexPosition = HPUtils::polarToCartesianCoordinates(*it);
				hpvec3 vertexNormal = vertexPosition - m_center;
				verticesAndNormals->push_back(vertexPosition);
				verticesAndNormals->push_back(vertexNormal);
				if (it != (*iter)->begin()){
					indices->push_back(i);
				}
					indices->push_back(i);
					i++;
			}
		indices->pop_back();
		}
	}
	}
	// draw Circle
	if(m_showCircle){
		int iTemp = i;
		int detail = 30;
		hpreal phi_c = (2*M_PI)/(float)detail;
		for (int j = 0; j < detail ; j++){
			hpvec3 vertexPosition = HPUtils::polarToCartesianCoordinates(hpvec3(j*phi_c,0.0f,RADIUS));
			hpvec3 vertexNormal = vertexPosition - m_center;

			verticesAndNormals->push_back(vertexPosition);
			verticesAndNormals->push_back(vertexNormal);
			if (j != 0){
				indices->push_back(i);
			}
			indices->push_back(i);
			i++;
		}
		indices->push_back(iTemp);
	}
	//draw generated Spline
	if(m_doLaneRiesenfeld == false && !m_doBSpline){
	if (m_generatedSpline->size()>0){
		int j=m_detail;
		for(vector<hpvec3>::iterator it = m_generatedSpline->begin(); it != m_generatedSpline->end(); ++it){
				hpvec3 vertexPosition = HPUtils::polarToCartesianCoordinates(*it);
				hpvec3 vertexNormal = vertexPosition - m_center;
				verticesAndNormals->push_back(vertexPosition);
				verticesAndNormals->push_back(vertexNormal);
				if (j%m_detail != 0){
					indices->push_back(i);
				}
				indices->push_back(i);
				if (j%m_detail == m_detail-1)
					indices->pop_back();
				i++;
				j++;
			}

	}
	}
	if(m_doLaneRiesenfeld == true && !m_doBSpline){
		if (m_generatedSpline->size()>0){

			for(vector<hpvec3>::iterator it = m_generatedSpline->begin(); it != m_generatedSpline->end(); ++it){
					hpvec3 vertexPosition = HPUtils::polarToCartesianCoordinates(*it);
					hpvec3 vertexNormal = vertexPosition - m_center;
					verticesAndNormals->push_back(vertexPosition);
					verticesAndNormals->push_back(vertexNormal);
					if (it != m_generatedSpline->begin()){
						indices->push_back(i);
					}
					indices->push_back(i);

					i++;

				}
			indices->pop_back();
		}
	}
	return new LineMesh3D(verticesAndNormals, indices);
}

PointCloud* FocalSpline::toPointCloud(){
	std::vector<hpvec3>* vertices = new std::vector<hpvec3>;
	if(!m_doBSpline){
	for(vector<vector<hpvec3>*>::iterator i=m_controlPoints->begin();i !=m_controlPoints->end();++i){
	if ((*i)->size()>0){
	for(vector<hpvec3>::iterator it = (*i)->begin(); it != (*i)->end(); ++it){
		vertices->push_back(HPUtils::polarToCartesianCoordinates(*it));

	}
	}
	}
	}
	/*
	// Draw Generated Spline as Points
	if (m_generatedSpline->size()>0){
	for(vector<hpvec3>::iterator it = m_generatedSpline->begin(); it != m_generatedSpline->end(); ++it){
			vertices->push_back(HPUtils::polarToCartesianCoordinates(*it));
	}
	}
	*/
	if(m_doBSpline){
		for(vector<hpvec3>::iterator it = m_BSplineControlPoints->begin(); it != m_BSplineControlPoints->end(); ++it){
					vertices->push_back(HPUtils::polarToCartesianCoordinates(*it));
		}
		for(vector<hpreal>::iterator it = m_BSplineKnots->begin(); it != m_BSplineKnots->end(); ++it){
						vertices->push_back(HPUtils::polarToCartesianCoordinates(hpvec3(*it,0,1.0f)));
		}
	}
	// draw Center
	if(m_showCircle)
		vertices->push_back(m_center);
	return new PointCloud(vertices);

}


int FocalSpline::getDegree(int selectionIndex){
	int bezierCurveIndex = 0;
	if (selectionIndex >= 0)
		bezierCurveIndex = calculateFocalBezierCurveIndexFromPointIndex(selectionIndex);

	return m_controlPoints->at(bezierCurveIndex)->size()-1;
}

void FocalSpline::removeControlPoint(int index){
	int bezierCurveIndex = calculateFocalBezierCurveIndexFromPointIndex(index);
	int currentIndex = calculatePointIndexFromBezierIndex(bezierCurveIndex,index);
	m_controlPoints->at(bezierCurveIndex)->erase(m_controlPoints->at(bezierCurveIndex)->begin()+currentIndex);
	if (currentIndex > 1)
		adjustControlPoints(bezierCurveIndex,currentIndex-1);
	m_focalBezierCurves.at(bezierCurveIndex)->update(m_phi,m_controlPoints->at(bezierCurveIndex));
	update();

}

void FocalSpline::removeControlPoint(int FocalBezierIndex, int pointIndex){
	int bezierCurveIndex = 0;
	if (FocalBezierIndex > 0)
		bezierCurveIndex = calculateFocalBezierCurveIndexFromPointIndex(FocalBezierIndex);
	m_controlPoints->at(bezierCurveIndex)->erase(m_controlPoints->at(bezierCurveIndex)->begin()+pointIndex);
	if (pointIndex > 1)
		adjustControlPoints(bezierCurveIndex,pointIndex-1);
	m_focalBezierCurves.at(bezierCurveIndex)->update(m_phi,m_controlPoints->at(bezierCurveIndex));
	update();
}

void FocalSpline::setDetail(int detail){
	m_detail = detail;
	if(!m_doLaneRiesenfeld)
		update();
}

int FocalSpline::calculateFocalBezierCurveIndexFromPointIndex(int pointIndex){
	int indexCounter = -1;
	int finalIndex = 0;
	while(indexCounter < pointIndex){
		indexCounter += m_controlPoints->at(finalIndex)->size();
		finalIndex++;
	}

	return finalIndex - 1;
}

int FocalSpline::calculatePointIndexFromBezierIndex(int bezierIndex, int pointIndex){
  int finalIndex = pointIndex;
  for(int i=0; i<bezierIndex; i++){
	  finalIndex = finalIndex-m_controlPoints->at(i)->size();
  }
  return finalIndex;
}

void FocalSpline::extendSpline(){
	vector<hpvec3>* newPoints = new vector<hpvec3>;
	hpvec3 firstPoint = m_controlPoints->back()->back();
	newPoints->push_back(firstPoint);
	newPoints->push_back(firstPoint + hpvec3(m_phi,0.0f,0.0f));
	newPoints->push_back(firstPoint + hpvec3(2*m_phi,0.0f,0.0f));
	m_controlPoints->push_back(newPoints);
	m_focalBezierCurves.push_back(new FocalBezierCurve(m_phi,newPoints));
	update();
}

void FocalSpline::generateLaneRiesenfeld(int n,int m){
	vector<hpvec3>* lrControlPoints = new vector<hpvec3>;
	lrControlPoints->push_back(m_controlPoints->at(0)->at(0));
	for(int i=0;i<m_controlPoints->size();i++){
		for(int j=1; j<m_controlPoints->at(i)->size();j++){
			lrControlPoints->push_back(m_controlPoints->at(i)->at(j));
		}
	}
	*m_generatedSpline=*lrControlPoints;
	for (int i = 0; i < m ; i ++){
		m_generatedSpline = duplicatePointsOfPolygon(m_generatedSpline);
		for (int j = 0; j< n; j++){
			m_generatedSpline = findMidPointsOfPolygon(m_generatedSpline);
		}
	}

}

vector<hpvec3>* FocalSpline::duplicatePointsOfPolygon(vector<hpvec3>* polygonPoints){

	vector<hpvec3>* doublePoints = new vector<hpvec3>;
	for(int i=0; i < polygonPoints->size();i++){
		doublePoints->push_back(polygonPoints->at(i));
		doublePoints->push_back(polygonPoints->at(i));

	}
	return doublePoints;
}

vector<hpvec3>* FocalSpline::findMidPointsOfPolygon(vector<hpvec3>* polygonPoints){

	vector<hpvec3>* midPoints = new vector<hpvec3>;
		if(polygonPoints->size() > 0){
				for(int i = 0; i<polygonPoints->size()-1; i++){
				midPoints->push_back(findMidPointOf(polygonPoints->at(i),polygonPoints->at(i+1)));

			}
		}
	return midPoints;
}

hpvec3 FocalSpline::findMidPointOf(hpvec3 p1,hpvec3 p2){
	hpreal phi = p2.x - p1.x;
	if (phi == 0 && p1.z == p2.z)
		return p1;
	hpreal deltaPhi = (0.5)*phi;
	hpreal r1 = p1.z;
	hpreal r2 = p2.z;
	hpreal r1quad = r1*r1;
	hpreal r2quad = r2*r2;
	hpreal aquad = (r2quad + r1quad-(2*r2*r1*cos(phi)));
	hpreal a = sqrt(aquad);
	hpreal beta = acos((r2quad-r1quad-aquad)/(-2*r1*a));
	hpreal gamma = M_PI-deltaPhi-beta;
	hpreal radius = r1*sin(beta)/sin(gamma);
	return  hpvec3(p1.x+deltaPhi,0,radius);
}

void FocalSpline::doLaneRiesenfeld(bool checked){
	m_doLaneRiesenfeld = checked;
	update();
}

void FocalSpline::setLRDegree(int degree){
	m_LRDegree = degree;
	if(m_doLaneRiesenfeld)
		update();
}

int FocalSpline::getLRDegree(){
	return m_LRDegree;
}

void FocalSpline::setLRIterations(int iterations){
	m_LRIterations = iterations;
	if(m_doLaneRiesenfeld)
		update();
}

int FocalSpline::getLRIterations(){
	return m_LRIterations;
}

int FocalSpline::getPhi(int index){
	int bezierCurveIndex;
	if (index < 0){
		bezierCurveIndex = 0;
	}
	else
		bezierCurveIndex=calculateFocalBezierCurveIndexFromPointIndex(index);
	return m_focalBezierCurves.at(bezierCurveIndex)->getPhi() ;
}

void FocalSpline::showControlPolygon(bool checked){
	m_showControlPolygon = checked;
	update();
}

void FocalSpline::showCircle(bool checked){
	m_showCircle = checked;
	update();
}

