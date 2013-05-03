#include "RayCloudTriangulatorBPA.h"

RayCloudTriangulatorBPA::RayCloudTriangulatorBPA(hpreal radius) : m_radius(radius) {}

RayCloudTriangulatorBPA::~RayCloudTriangulatorBPA() {}

TriangleMesh3D* RayCloudTriangulatorBPA::triangulate(const RayCloud3D& rays) {
	//TODO
	return 0;
}

TriangleMesh2D* RayCloudTriangulatorBPA::triangulate(const PointCloud2D& points, const hpvec3& origin, const hpvec3& normal) {
	//TODO
	return 0;
}
