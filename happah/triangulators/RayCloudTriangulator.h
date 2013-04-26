#ifndef RAY_CLOUD_TRIANGULATOR_H
#define RAY_CLOUD_TRIANGULATOR_H

#include "happah/HappahTypes.h"
#include "happah/geometries/Mesh.h"

class RayCloudTriangulator {

public:
	virtual ~RayCloudTriangulator() {};

	virtual TriangleMesh* triangulate(RayCloud3D& rays) = 0;
	virtual TriangleMesh* triangulate(PointCloud2D& points, hpvec3& origin, hpvec3& normal) = 0;

};


#endif
