#pragma once

#include "happah/triangulators/PlanarGraphTriangulator.h"

class PlanarGraphTriangulatorSeidel : public PlanarGraphTriangulator {

public:
	//returns trapezoidal decomposition of the interior of the given polygon according to Seidel's algorithm
	//static TrapezoidMesh2D* trapezoidulate(PlanarGraphSegmentIterator first, PlanarGraphSegmentIterator last); // Alternative 1
	//static void trapezoidulate(PlanarGraphSegmentIterator first, PlanarGraphSegmentIterator last, TrapezoidMesh2D& trapezoidMesh); // Alternative 2

	PlanarGraphTriangulatorSeidel();
	~PlanarGraphTriangulatorSeidel();

	TriangleMesh2D* triangulate(PlanarGraphSegmentIterator first, PlanarGraphSegmentIterator last);

	class TrapezoidMesh2D {
		//TODO
	public:
		//LineMesh2D* toLineMesh(); //TODO
		//TriangleMesh2D* toTriangleMesh();
	};

};
