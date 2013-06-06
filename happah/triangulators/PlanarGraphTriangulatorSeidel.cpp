#include "happah/triangulators/PlanarGraphTriangulatorSeidel.h"

PlanarGraphTriangulatorSeidel::PlanarGraphTriangulatorSeidel() {}

PlanarGraphTriangulatorSeidel::~PlanarGraphTriangulatorSeidel() {}

TriangleMesh2D* PlanarGraphTriangulatorSeidel::triangulate(PlanarGraphSegmentEndpointsIterator first, PlanarGraphSegmentEndpointsIterator last) {
	/*
	Alternative 1
	TrapezoidMesh2D* trapezoidMesh = trapezoidulate(first, last);
	if(trapezoidMesh == 0) return 0;
	TriangleMesh2D* triangleMesh = trapezoidMesh->toTriangleMesh();
	delete trapezoidMesh;
	return triangleMesh;
	
	Alternative 2
	TrapezoidMesh2D trapezoidMesh;
	trapezoidulate(first, last, trapezoidMesh);
	return trapezoidMesh.toTriangleMesh();
	*/
	

	TrapezoidMesh2D* trapezoidMesh = trapezoidulate(first, last);
	if(trapezoidMesh == 0) return 0;
	TriangleMesh2D* triangleMesh = trapezoidMesh->toTriangleMesh();
	delete trapezoidMesh;
	return triangleMesh;

}

static TrapezoidMesh2D* PlanarGraphTriangulatorSeidel::trapezoidulate(PlanarGraphSegmentEndpointsIterator first, PlanarGraphSegmentEndpointsIterator last) {

	Node* root = new Sink(new Trapezoid());

	for(auto it = first; it != last; it++) {
		SegmentEndpoints2D segment = *it;
		hpvec2 upper = (segment.a.y > segment.b.y)
						? segment.a
						: segment.b;
		hpvec2 lower = (segment.a.y <= segment.b.y)
						? segment.a
						: segment.b;
		Trapezoid* upperTrapezoid = root->getTrapezoid(upper);
		upperTrapezoid->splitHorizontal(upper);
		Trapezoid* lowerTrapezoid = root->getTrapezoid(lower);
		lowerTrapezoid->splitHorizontal(lower);
		Trapezoid* current = upperTrapezoid;
		Trapezoid* next;
		while(current != lowerTrapezoid) {
			next = current->getNextAlongSegment(segment);
			current->splitVertical(segment);
			current = next;
		}
	}
}

void PlanarGraphTriangulatorSeidel::Trapezoid::splitHorizontal(hpvec2& point) {
	
	YNode* yNode = sink->splitHorizontal(point.y);

	Trapezoid* upper = new Trapezoid(yNode->getChild1());
	Trapezoid* lower = new Trapezoid(yNode->getChild2());

	upper->leftSegment = leftSegment;
	lower->leftSegment = leftSegment;
	upper->rightSegment = rightSegment;
	lower->rightSegment = rightSegment;
	
	upper->upperLeft = upperLeft;
	upper->upperRight = upperRight;
	lower->lowerLeft = lowerLeft;
	lower->lowerRight = lowerRight;

	upper->lowerLeft = lower;
	lower->upperLeft = upper;

	delete this;
}

void PlanarGraphTriangulatorSeidel::Trapezoid::splitVertical(SegmentEndpoints2D& segment) {

	XNode* xNode = sink->splitVertical(segment);

	Trapezoid* left = new Trapezoid(xNode->getChild1());
	Trapezoid* right = new Trapezoid(xNode->getChild2());

	left->leftSegment = leftSegment;
	right->rightSegment = rightSegment;
	left->rightSegment = &segment;
	right->leftSegment = &segment;

	left->upperLeft = upperLeft;
}




