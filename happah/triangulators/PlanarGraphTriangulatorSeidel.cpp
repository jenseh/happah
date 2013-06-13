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

	if(upperLeft->lowerLeft == this)
		upperLeft->lowerLeft = upper;
	if(upperRight->lowerLeft == this)
		upperRight->lowerLeft = upper;
	if(upperLeft->lowerRight == this)
		upperLeft->lowerRight = upper;
	if(upperRight->lowerRight == this)
		upperRight->lowerRight = upper;

	if(lowerLeft->upperLeft == this)
		lowerLeft->upperLeft = lower;
	if(lowerRight->upperLeft == this)
		lowerRight->upperLeft = lower;
	if(lowerLeft->upperRight == this)
		lowerLeft->upperRight = lower;
	if(lowerRight->upperRight == this)
		lowerRight->upperRight = lower;

	delete this;
}

void PlanarGraphTriangulatorSeidel::Trapezoid::splitVertical(SegmentEndpoints2D& segment) {

	Trapezoid* left = new Trapezoid();
	Trapezoid* right = new Trapezoid();

	XNode* xNode = sink->splitVertical(segment, left, right);

	left->setSink(xNode->getChild1());
	right->setSink(xNode->getChild2());

	left->leftSegment = leftSegment;
	right->rightSegment = rightSegment;
	left->rightSegment = &segment;
	right->leftSegment = &segment;

	left->upperLeft = upperLeft;
	right->upperRight = upperRight;

	///TODO
}



Trapezoid* PlanarGraphTriangulatorSeidel::XNode::getTrapezoid(const hpvec2& point) {
	hpdouble m = (key->b->y - key->a->y) / (key->b->x - key->a->x);
	hpdouble b = key->a->y - m * key->a->x;
	hpdouble x = (point->y - b) / m;
	return (point.x > x)
			? child1->getTrapezoid(point)
			: child2->getTrapezoid(point);
}

Trapezoid* PlanarGraphTriangulatorSeidel::YNode::getTrapezoid(const hpvec2& point) {

	return (point.y > key)
			? child1->getTrapezoid(point)
			: child2->getTrapezoid(point);
}

Trapezoid* PlanarGraphTriangulatorSeidel::Sink::getTrapezoid(const hpvec2& point) {

	return trapezoid;
}

YNode* PlanarGraphTriangulatorSeidel::Sink::splitHorizontal(const hpdouble& yValue, Trapezoid* upper, Trapezoid* lower) {
	
	YNode yNode = new YNode(yValue);
	
	yNode->child1 = new Sink(upper);
	yNode->child2 = new Sink(lower);

	delete this;

	return yNode;
}

XNode* PlanarGraphTriangulatorSeidel::Sink::splitVertical(SegmentEndpoints2D& segment, Trapezoid* left, Trapezoid* right) {
	
	XNode xNode = new XNode(segment);
	
	xNode->child1 = new Sink(left);
	xNode->child2 = new Sink(right);

	delete this;

	return xNode;
}





