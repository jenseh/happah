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
	void handleSelection();
	void handleSelection(int pointIndex);

private:
    hpvec3 cartesianToPolarCoordinates(hpvec3 cartesian);
    hpvec3 polarToCartesianCoordinates(hpvec3 polar);
	vector<hpvec3>* m_controlPoints;
	vector<hpvec3>* m_generatedSpline;
	hpvec3 m_center;
	hpreal m_radius;
	hpreal m_phi;
};
typedef shared_ptr<FocalSpline> FocalSpline_ptr;

#endif /* FOCALSPLINE_H_ */
