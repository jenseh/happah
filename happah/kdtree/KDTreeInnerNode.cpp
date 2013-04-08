#include "KDTreeInnerNode.h"

template <class T>
class TriangleSorter {
      int axis;
public:
      TriangleSorter(int axis_) : axis(axis_) {}
      bool operator()(const T& a, const T& b) {
        return a.vertices[0][axis] < b.vertices[0][axis];
      }
};



KDTreeInnerNode::KDTreeInnerNode(std::vector<Triangle>* triangles, BBox& bBox, hpuint depth, hpuint maxTrianglesPerBox, int terminateDepth )
{
	//TODO: Something goes wrong here, sometimes all the triangles are put into left side
  m_bBox = bBox;
  m_axis = depth % 3;
  unsigned int size = triangles->size();
  // Sort triangles (point A) along an axis
  std::sort(triangles->begin(), triangles->end(), TriangleSorter<Triangle>(m_axis));

  // Determine where separating axis should be
  unsigned int middleTPos = size / 2;
  m_axisValue = triangles->at(middleTPos).vertices[0][m_axis];

  std::vector<Triangle>* leftTriangles = new std::vector<Triangle>;
  std::vector<Triangle>* rightTriangles = new std::vector<Triangle>;
  BBox leftBox;
  BBox rightBox;
  std::vector<Triangle>::iterator pos = triangles->begin();
  std::vector<Triangle>::iterator end = triangles->end();
  for (; pos != end; pos++) {
      Triangle triangle = *pos;

      if (triangle.vertices[0][m_axis] <= m_axisValue
          || triangle.vertices[1][m_axis] <= m_axisValue
          || triangle.vertices[2][m_axis] <= m_axisValue) {
          leftTriangles->push_back(triangle);
          leftBox.addTriangle(triangle);
      }

      if (triangle.vertices[0][m_axis] > m_axisValue
          || triangle.vertices[1][m_axis] > m_axisValue
          || triangle.vertices[2][m_axis] > m_axisValue) {
          rightTriangles->push_back(triangle);
          rightBox.addTriangle(triangle);
      }
  }

  // If all in one node
  if( leftTriangles->size() == triangles->size() || rightTriangles->size() == triangles->size() ){
	  // If all triangles are put in one node there should only be 2 more inner nodes untill the algorithm is forces to quit
	  if( terminateDepth == -1 ) {
		  terminateDepth = depth +2;
	  }
	  if( depth == terminateDepth ) {
		  m_leftChild = new KDTreeLeaf(triangles, depth +1);
	  }else {
		  m_leftChild = new KDTreeInnerNode(triangles, leftBox, depth + 1, maxTrianglesPerBox, terminateDepth);
	  }
	  std::vector<Triangle>* emptyList = new std::vector<Triangle>;
	  m_rightChild = new KDTreeLeaf(emptyList, depth +1);
	  return;
  }
  // Determine whether to set an inner node or leaf for each child
  if (leftTriangles->size() > maxTrianglesPerBox ) {
      m_leftChild = new KDTreeInnerNode(leftTriangles, leftBox, depth + 1, maxTrianglesPerBox);
      delete leftTriangles;
  } else {
      m_leftChild = new KDTreeLeaf(leftTriangles, depth + 1);
  }

  if (rightTriangles->size() > maxTrianglesPerBox) {
      m_rightChild = new KDTreeInnerNode(rightTriangles, rightBox, depth + 1, maxTrianglesPerBox);
      delete rightTriangles;
  } else {
      m_rightChild = new KDTreeLeaf(rightTriangles, depth + 1);
  }
}

KDTreeInnerNode::~KDTreeInnerNode(){
	delete m_leftChild;
	delete m_rightChild;
}

bool KDTreeInnerNode::intersectAll(Circle& intersector, std::list<CircleHitResult*>* hitResults, BBox& intersectorBox, int depth) {

  if (intersectorBox.intersects(m_bBox)) {

      // Continue with respective child node
      bool intersectA = false;
      bool intersectB = false;

      intersectA = m_leftChild->intersectAll(intersector, hitResults, intersectorBox, depth + 1);
      intersectB = m_rightChild->intersectAll(intersector, hitResults, intersectorBox, depth + 1);

      return (intersectA || intersectB);
    } else {
      return false;
    }
}

hpreal KDTreeInnerNode::intersectFirst(Ray& intersector, hpreal maxLength){
	if( intersector.intersects(m_bBox, maxLength)){
		maxLength = std::min(maxLength, m_leftChild->intersectFirst(intersector, maxLength));
		maxLength = std::min(maxLength, m_rightChild->intersectFirst(intersector, maxLength));
	}
	return maxLength;
}
