#ifndef RAY_CLOUD_TRIANGULATOR_BPA_H
#define RAY_CLOUD_TRIANGULATOR_BPA_H

#include "happah/triangulators/RayCloudTriangulator.h"

class RayCloudTriangulatorBPA : public RayCloudTriangulator {
	

public:
	RayCloudTriangulatorBPA(hpreal radius);
	~RayCloudTriangulatorBPA();

	TriangleMesh3D* triangulate(const RayCloud3D& rays);
	TriangleMesh2D* triangulate(const PointCloud2D& points, const hpvec3& origin, const hpvec3& normal);
	

private:
	hpreal m_radius;
	hpreal m_diameter;
	
	hpvec3 m_MinVec;

	float m_XMin;
	float m_YMin;
	float m_ZMin;
	float m_XMax;
	float m_YMax;
	float m_ZMax;

	unsigned int m_RaySize;
	unsigned int m_GridSize;	

	unsigned int m_nXvoxels;
	unsigned int m_nYvoxels;
	unsigned int m_nZvoxels;

	vector<int> grid;
	vector<int> nexts;

	void initializeGrid(const RayCloud3D& rays);
	unsigned int getIndex(const hpvec3& point);
	void testGrid(const RayCloud3D& rays);
	bool searchSeedTriangle(const RayCloud3D& rays, hpvec3& point1, hpvec3& point2, hpvec3& point3);
	void testSeedTriangle(const hpvec3& point1, const hpvec3& point2, const hpvec3& point3);
	unsigned int[] getNearVoxels(hpvec3 point);

};


#endif
