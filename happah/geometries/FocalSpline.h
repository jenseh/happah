#ifndef FOCALSPLINE_H_
#define FOCALSPLINE_H_

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
	void generateFocalSpline();
	LineMesh* toLineMesh();
	PointCloud* toPointCloud();
	void setPolarControlPoint(hpuint index, hpvec3 controlPoint);
	void setCartesianControlPoint(hpuint index, hpvec3 controlPoint);
	hpvec3 getPolarControlPoint(hpuint index);
	hpvec3 getCartesianControlPoint(hpuint index);
	void addControlPoint();
	void addControlPoint(hpvec3);
	void removeControlPoint(int index);
	int getDegree();
	void setDetail(int detail);



private:
    hpvec3 cartesianToPolarCoordinates(hpvec3 cartesian);
    hpvec3 polarToCartesianCoordinates(hpvec3 polar);
    void   generateNewControlPoints();
    void   adjustControlPoints(int index);
    hpvec3   calculateIntersection(hpvec3 a1,hpvec3 a2, hpvec3 b1, hpvec3 b2);
	vector<hpvec3>* m_controlPoints;
	vector<hpvec3>* m_currentControlPoints;
	vector<hpvec3>* m_generatedSpline;
	hpvec3 m_center;
	hpreal m_radius;
	hpreal m_phi;
	hpreal m_phiComplete;
	hpreal m_fraction;
	int    m_detail;
	int    m_currentDegree;

};
typedef shared_ptr<FocalSpline> FocalSpline_ptr;

#endif /* FOCALSPLINE_H_ */
