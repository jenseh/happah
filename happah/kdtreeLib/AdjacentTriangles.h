#ifndef ADJACENTTRIANGLES_H
#define ADJACENTTRIANGLES_H

#include "happah/geometries/TriangleMesh.h"


class AdjacentTriangles
{
public:
	struct Adjacents {
		hpuint adjacentsCount;
		int tiangleIndex[3];
	};

	AdjacentTriangles(const TriangleMesh3D_ptr triangleMesh);
	~AdjacentTriangles();
	int getAdjacentTrianglesIndices(const int triangleIndex, Adjacents& adjacents) const;
private:
	Adjacents* m_adjacentTriangles;
	hpuint m_inidicesCount;
	int getSameIndicesWithoutCurrent(vector<hpuint>& vertex_1, vector<hpuint>& vertex_2, hpuint currentIndex ) const;
};

#endif // ADJACENTTRIANGLES_H
