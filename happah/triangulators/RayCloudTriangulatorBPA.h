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
	float x_min;
	float y_min;
	float z_min;
	float x_max;
	float y_max;
	float z_max;
	const float FLOAT_MIN;
	const float FLOAT_MAX;

	int x_voxels;
	int y_voxels;
	int z_voxels;

	vector<int> grid;
	vector<int> nexts;

	void initializeGrid(const RayCloud3D& rays);
	int getIndex(const hpvec3& point);
	void testGrid(const RayCloud3D& rays);
	bool searchSeedTriangle(const RayCloud3D& rays, hpvec3& point1, hpvec3& point2, hpvec3& point3);
	void testSeedTriangle(const hpvec3& point1, const hpvec3& point2, const hpvec3& point3);

};


#endif
