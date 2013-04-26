#ifndef RAY_CLOUD_TRIANGULATOR_H
#define RAY_CLOUD_TRIANGULATOR_H

#include "happah/HappahTypes.h"
#include "happah/geometries/Mesh.h"

class RayCloudTriangulator {

public:
	virtual ~RayCloudTriangulator() {};

	virtual TriangleMesh* triangulate(const RayCloud3D& rays) = 0;
	virtual TriangleMesh* triangulate(const PointCloud2D& points, const hpvec3& origin, const hpvec3& normal) = 0;

};


#endif
