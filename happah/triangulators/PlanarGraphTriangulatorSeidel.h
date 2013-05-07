#pragma once

#include "happah/triangulators/PlanarGraphTriangulator.h"

class PlanarGraphTriangulatorSeidel : public PlanarGraphTriangulator {

public:
	//returns trapezoidal decomposition of the interior of the given polygon according to Seidel's algorithm
	//static TrapezoidMesh2D* trapezoidulate(PlanarGraphSegmentEndpointsIterator first, PlanarGraphSegmentEndpointsIterator last); // Alternative 1
	//static void trapezoidulate(PlanarGraphSegmentEndpointsIterator first, PlanarGraphSegmentEndpointsIterator last, TrapezoidMesh2D& trapezoidMesh); // Alternative 2

	PlanarGraphTriangulatorSeidel();
	~PlanarGraphTriangulatorSeidel();

	TriangleMesh2D* triangulate(PlanarGraphSegmentEndpointsIterator first, PlanarGraphSegmentEndpointsIterator last);

	class TrapezoidMesh2D {
		//TODO
	public:
		//LineMesh2D* toLineMesh(); //TODO
		//TriangleMesh2D* toTriangleMesh();
	};

};
