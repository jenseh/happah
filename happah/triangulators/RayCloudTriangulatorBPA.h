#ifndef RAY_CLOUD_TRIANGULATOR_BPA_H
#define RAY_CLOUD_TRIANGULATOR_BPA_H

#include "happah/triangulators/RayCloudTriangulator.h"

class RayCloudTriangulatorBPA : public RayCloudTriangulator {

public:
	RayCloudTriangulatorBPA(hpreal radius);
	~RayCloudTriangulatorBPA();

	TriangleMesh* triangulate(RayCloud3D& rays);
	TriangleMesh* triangulate(PointCloud2D& points, hpvec3& origin, hpvec3& normal);

private:
	hpreal m_radius;

};


#endif
