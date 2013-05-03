#include "happah/triangulators/PlanarGraphTriangulatorSeidel.h"

PlanarGraphTriangulatorSeidel::PlanarGraphTriangulatorSeidel() {}

PlanarGraphTriangulatorSeidel::~PlanarGraphTriangulatorSeidel() {}

TriangleMesh* PlanarGraphTriangulatorSeidel::triangulate(PlanarGraphSegmentIterator first, PlanarGraphSegmentIterator last) {
	/*
	Alternative 1
	TrapezoidMesh2D* trapezoidMesh = trapezoidulate(first, last);
	if(trapezoidMesh == 0) return 0;
	TriangleMesh* triangleMesh = trapezoidMesh->toTriangleMesh();
	delete trapezoidMesh;
	return triangleMesh;
	
	Alternative 2
	TrapezoidMesh2D trapezoidMesh;
	trapezoidulate(first, last, trapezoidMesh);
	return trapezoidMesh.toTriangleMesh();
	*/
	//TODO
	return 0;
}
