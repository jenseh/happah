#pragma once

#include "happah/triangulators/PlanarGraphTriangulator.h"

class PlanarGraphTriangulatorSeidel : public PlanarGraphTriangulator {

public:
	//returns trapezoidal decomposition of the interior of the given polygon according to Seidel's algorithm
	static TrapezoidMesh2D* trapezoidulate(PlanarGraphSegmentEndpointsIterator first, PlanarGraphSegmentEndpointsIterator last); // Alternative 1
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

	class Trapezoid {
		
		public:
			void splitHorizontal(hpvec2& point);
			void splitVertical(SegmentEndpoints2D& segment);

			void setSink(Sink* sink) {this->sink = sink;};

		private:
			Sink* sink;

			SegmentEndpoints* leftSegment = NULL;
			SegmentEndpoints* rightSegment = NULL;

			Trapezoid* upperLeft = NULL;
			Trapezoid* upperMiddle = NULL;
			Trapezoid* upperRight = NULL;
			Trapezoid* lowerLeft = NULL;
			Trapezoid* lowerRight = NULL;
	}

	class Node {
		
		public:
			virtual Trapezoid* getTrapezoid(const hpvec2& point) = 0;

			Node* getChild1() {return child1;};
			Node* getChild2() {return child2;};
			Node* getParent() {return parent;};

		private:
			Node* child1 = NULL;
			Node* child2 = NULL;
			Node* parent = NULL;
	}

	class XNode : public Node {
		
		public:
			XNode(SegmentEndpoints2D* key) : key(key) {};
			Trapezoid* getTrapezoid(const hpvec2& point);

		private:
			SegmentEndpoints2D* key;
	}

	class YNode : public Node {
		
		public:
			YNode(hpdouble key) : key(key) {};
			Trapezoid* getTrapezoid(const hpvec2& point);

		private:
			hpdouble key;
	}

	class Sink : public Node {

		public:

			Sink(Trapezoid* trapezoid) : trapezoid(trapezoid) {
				trapezoid->setSink(this);			
			};

			Trapezoid* getTrapezoid(const hpvec2& point);
			YNode* splitHorizontal(const hpdouble& yValue, Trapezoid* upper, Trapezoid* lower);
			XNode* splitVertical(SegmentEndpoints2D& segment, Trapezoid* left, Trapezoid* right);

		private:
			Trapezoid* trapezoid;
	}
};


