#ifndef FOCALSPLINE_H_
#define FOCALSPLINE_H_

#include "happah/HappahTypes.h"
#include "happah/geometries/FocalBezierCurve.h"
#include "happah/geometries/Geometry.h"
#include "happah/geometries/PointCloud.h"
#include "happah/geometries/LineMesh.h"
#include <vector>
#include <memory>

using namespace std;

class FocalSpline : public Geometry {
public:
	FocalSpline();
	virtual ~FocalSpline();
	void init(int degree);
	void update();

	LineMesh3D* toLineMesh();
	PointCloud* toPointCloud();
	void setControlPoint(hpuint index, hpvec3 controlPoint);
	hpvec3 getControlPoint(hpuint index);
	void addControlPoint(int selectionIndex);
	void addControlPoint(hpvec3);
	void removeControlPoint(int index);
	void removeControlPoint(int FocalBezierIndex, int pointIndex);
	int getDegree(int index);
	void setDetail(int detail);
	void extendSpline();
	void doLaneRiesenfeld(bool checked);
	void setLRIterations(int degree);
	int  getLRIterations();
	void setLRDegree(int degree);
	int getLRDegree();
	int getPhi(int index);
	void showControlPolygon(bool checked);
	void showCircle(bool checked);

private:

    void   generateNewControlPoints();
    void   adjustControlPoints(int bezierCurveIndex,int currentIndex,int direction = 0);
    int    calculateFocalBezierCurveIndexFromPointIndex(int pointIndex);
    int    calculatePointIndexFromBezierIndex(int bezierIndex, int pointIndex);
    void generateFocalSpline(int i);
    void generateLaneRiesenfeld(int n,int m);
    vector<hpvec3>* duplicatePointsOfPolygon(vector<hpvec3>*points);
    vector<hpvec3>* findMidPointsOfPolygon(vector<hpvec3>*points);
    hpvec3 findMidPointOf(hpvec3 point1, hpvec3 point2);
    vector<FocalBezierCurve*> m_focalBezierCurves;
	vector<vector<hpvec3>*>* m_controlPoints;
	vector<hpvec3>* m_generatedSpline;
	hpvec3 m_center;
	hpreal m_phi;
	hpreal m_phiComplete;
	bool   m_doLaneRiesenfeld;
	int    m_detail;
	int m_LRIterations;
	int m_LRDegree;
	bool  m_showControlPolygon;
	bool  m_showCircle;

};
typedef shared_ptr<FocalSpline> FocalSpline_ptr;

#endif /* FOCALSPLINE_H_ */
