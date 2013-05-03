#pragma once

#include "happah/geometries/Segment.h"
#include "happah/geometries/TriangleMesh.h"

#include <iterator>

using namespace std;

typedef iterator<random_access_iterator_tag, const Segment2D> PlanarGraphSegmentIterator;

class PlanarGraphTriangulator {

public:
	static const PlanarGraphTriangulator& TRIANGULATOR;

	PlanarGraphTriangulator();
	virtual ~PlanarGraphTriangulator();

	virtual TriangleMesh2D* triangulate(PlanarGraphSegmentIterator first, PlanarGraphSegmentIterator last) = 0;

};
