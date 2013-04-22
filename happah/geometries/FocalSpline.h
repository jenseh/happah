#ifndef FOCALSPLINE_H_
#define FOCALSPLINE_H_

#include "happah/geometries/FocalBezierCurve.h"
#include "happah/geometries/Geometry.h"
#include "happah/HappahTypes.h"
#include "happah/geometries/Mesh.h"
#include "happah/geometries/PointCloud.h"
#include <vector>
#include <memory>

using namespace std;

class FocalSpline : public Geometry {
public:
	FocalSpline();
	virtual ~FocalSpline();
	void init(int degree);
	void update();

	LineMesh* toLineMesh();
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



private:

    void   generateNewControlPoints();
    void   adjustControlPoints(int bezierCurveIndex,int currentIndex);
    int    calculateFocalBezierCurveIndexFromPointIndex(int pointIndex);
    int    calculatePointIndexFromBezierIndex(int bezierIndex, int pointIndex);
    void generateFocalSpline(int i);
    vector<FocalBezierCurve*> m_focalBezierCurves;
	vector<vector<hpvec3>*>* m_controlPoints;
	vector<hpvec3>* m_generatedSpline;
	hpvec3 m_center;
	hpreal m_phi;
	hpreal m_phiComplete;
	hpreal m_fraction;
	int    m_detail;

};
typedef shared_ptr<FocalSpline> FocalSpline_ptr;

#endif /* FOCALSPLINE_H_ */
