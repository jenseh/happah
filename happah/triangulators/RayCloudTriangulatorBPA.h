#ifndef RAY_CLOUD_TRIANGULATOR_BPA_H
#define RAY_CLOUD_TRIANGULATOR_BPA_H

#include "happah/triangulators/RayCloudTriangulator.h"

class RayCloudTriangulatorBPA : public RayCloudTriangulator {

public:
	RayCloudTriangulatorBPA(hpreal radius);
	~RayCloudTriangulatorBPA();

	TriangleMesh* triangulate(const RayCloud3D& rays);
	TriangleMesh* triangulate(const PointCloud2D& points, const hpvec3& origin, const hpvec3& normal);

private:
	hpreal m_radius;

};


#endif
