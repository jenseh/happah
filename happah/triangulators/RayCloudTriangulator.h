#ifndef RAY_CLOUD_TRIANGULATOR_H
#define RAY_CLOUD_TRIANGULATOR_H

#include "happah/HappahTypes.h"
#include "happah/geometries/TriangleMesh.h"

class RayCloudTriangulator {

public:
	virtual ~RayCloudTriangulator() {};

	virtual TriangleMesh3D* triangulate(const RayCloud3D& rays) = 0;
	virtual TriangleMesh2D* triangulate(const PointCloud2D& points, const hpvec3& origin, const hpvec3& normal) = 0;

};


#endif
