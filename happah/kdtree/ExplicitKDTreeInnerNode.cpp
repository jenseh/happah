#include "ExplicitKDTreeInnerNode.h"

template <class T>
class TriangleSorter {
      int axis;
public:
      TriangleSorter(int axis_) : axis(axis_) {}
      bool operator()(T* a, T* b) {
        return a->vertices[0][axis] < b->vertices[0][axis];
      }
};



ExplicitKDTreeInnerNode::ExplicitKDTreeInnerNode(std::vector<Triangle*>* triangles, BBox* bBox, int depth)
{
//  std::cout << "Creating at depth: " << depth << " with size: " << triangles->size() << std::endl;

//  for (unsigned int i = 0; i < triangles->size(); i++) {
//    for (int i=0; i<3; i++) {
//        for (int j=0; j<3; j++) {
//            if ((triangles[i]->vertices[i][j] < -1000.0f || triangles[i]->vertices[i][j] > 1000.0f)
//                || (triangles[i]->vertices[i][j] < -1000.0f || triangles[i]->vertices[i][j] > 1000.0f)
//                || (triangles[i]->vertices[i][j] < -1000.0f || triangles[i]->vertices[i][j] > 1000.0f))
//              {
//                std::cout << "triangleA: " << triangles[i]->vertices[0].x << ", " << triangles[i]->vertices[0].y << ", " << triangles[i]->vertices[0].z << std::endl;
//                std::cout << "triangleB: " << triangles[i]->vertices[1].x << ", " << triangles[i]->vertices[1].y << ", " << triangles[i]->vertices[1].z << std::endl;
//                std::cout << "triangleC: " << triangles[i]->vertices[2].x << ", " << triangles[i]->vertices[2].y << ", " << triangles[i]->vertices[2].z << std::endl;
//              }
//          }
//      }
//  }

  m_bBox = bBox;
  m_axis = depth % 3;
  unsigned int size = triangles->size();

  const unsigned int maxTrianglesPerBox = 500;

  // Sort triangles (point A) along an axis
  std::sort(triangles->begin(), triangles->end(), TriangleSorter<Triangle>(m_axis));

  // Determine where separating axis should be
  unsigned int middleTPos = size / 2;
  m_axisValue = triangles->at(middleTPos)->vertices[0][m_axis];

  std::vector<Triangle*>* leftTriangles = new std::vector<Triangle*>;
  std::vector<Triangle*>* rightTriangles = new std::vector<Triangle*>;

  std::vector<Triangle*>::iterator pos = triangles->begin();
  std::vector<Triangle*>::iterator end = triangles->end();
  for (; pos != end; pos++) {
      Triangle* triangle = *pos;

      if (triangle->vertices[0][m_axis] <= m_axisValue
          || triangle->vertices[1][m_axis] <= m_axisValue
          || triangle->vertices[2][m_axis] <= m_axisValue) {
          leftTriangles->push_back(triangle);
      }

      if (triangle->vertices[0][m_axis] > m_axisValue
          || triangle->vertices[1][m_axis] > m_axisValue
          || triangle->vertices[2][m_axis] > m_axisValue) {
          rightTriangles->push_back(triangle);
      }
  }

  // Split bounding box to get child boxes
  std::vector<BBox*> boxes = bBox->split(m_axis, m_axisValue);
  if (boxes.size() != 2) {
      std::cerr << "Error: Splitting returned invalid size!";
      exit(1);
    }

  // Determine whether to set an inner node or leaf for each child
  if (leftTriangles->size() > maxTrianglesPerBox) {
      m_leftChild = new ExplicitKDTreeInnerNode(leftTriangles, boxes[0], depth + 1);
  } else {
//      std::cout << "Building left leaf at depth: " << depth << " with size " << leftTriangles->size() << std::endl;
      m_leftChild = new ExplicitKDTreeLeaf(leftTriangles, depth + 1);
  }

  if (rightTriangles->size() > maxTrianglesPerBox) {
      m_rightChild = new ExplicitKDTreeInnerNode(rightTriangles, boxes[1], depth + 1);
  } else {
//      std::cout << "Building right leaf at depth: " << depth << " with size " << rightTriangles->size() << std::endl;
      m_rightChild = new ExplicitKDTreeLeaf(rightTriangles, depth + 1);
  }
}

bool ExplicitKDTreeInnerNode::intersectAll(Circle& intersector, std::list<CircleHitResult*>* hitResults, BBox* intersectorBox, int depth) {

  if (intersectorBox->intersects(m_bBox)) {

      // Continue with respective child node
      bool intersectA = false;
      bool intersectB = false;

      intersectA = m_leftChild->intersectAll(intersector, hitResults, intersectorBox, depth + 1);
      intersectB = m_rightChild->intersectAll(intersector, hitResults, intersectorBox, depth + 1);

      return (intersectA || intersectB);
    } else {
//      std::cout << "Not intersected at depth: " << depth << std::endl;
      return false;
    }
}
