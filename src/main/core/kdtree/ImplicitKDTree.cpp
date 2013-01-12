#include "ImplicitKDTree.h"


template <class T>
class TriangleSorter {
      int axis;
public:
      TriangleSorter(int axis_) : axis(axis_) {}
      bool operator()(T* a, T* b) {
        return a->vertices[0][axis] < b->vertices[0][axis];
      }
};


struct TodoItem {
  int kPos;
  int minTPos;
  int maxTPos;

  TodoItem(int kPos_, int minTPos_, int maxTPos_) {
    kPos = kPos_;
    minTPos = minTPos_;
    maxTPos = maxTPos_;
  }
};

int depthFromKPos(int kPos) {
  int depth = 0;
  while (kPos >>= 1) ++depth;
  return depth;
}

// Criteria for subdivision are:
// - A maximum number of triangles in a box
// - No progress from depth d to d+1

// Shortcuts: T for triangle and K for tree
ImplicitKDTree::ImplicitKDTree(std::vector<Triangle*>& triangles) : m_triangles(triangles)
{
  // Construct the KDTree
  std::cout << "Constructing KDTree" << std::endl;
  std::cout << "Triangle count: " << triangles.size() << std::endl;


  const int maxTrianglesPerBox = 5;
  std::list<TodoItem> todo;
  todo.push_back(TodoItem(0, 0, m_triangles.size() - 1));

  for (std::list<TodoItem>::iterator i = todo.begin(); i != todo.end(); i++) {
      TodoItem todoItem = *i;
      int kPos = todoItem.kPos;
      int minTPos = todoItem.minTPos;
      int maxTPos = todoItem.maxTPos;
      int size = maxTPos - minTPos;

      // Determine axis along which we will sort next
      int depth = depthFromKPos(kPos);
      int axis = depth % 3;

      if (size > maxTrianglesPerBox) {
        // Sort triangles (point A) along an axis
        std::sort(m_triangles.begin() + minTPos, m_triangles.begin() + maxTPos, TriangleSorter<Triangle>(axis));

        // Determine where separating axis should be
        int middleTPos = (minTPos + maxTPos) / 2;
        float axisValue = m_triangles[middleTPos]->vertices[0].x;

        // Determine where separating axis actually is
        for (; middleTPos < maxTPos; middleTPos++) {
            float nextAxisValue = m_triangles[middleTPos + 1]->vertices[0][axis];
            if (nextAxisValue != axisValue) {
                break;
            }
        }

        // Correct middleTPos if bigger than maxTPos
        int rightMiddleTPos = middleTPos < maxTPos ? middleTPos : maxTPos;

        // Add indices of left and right child to the todo list
  //      std::cout << minTPos << " " << middleTPos << " " << maxTPos << std::endl;
        todo.push_back(TodoItem(2 * kPos + 1, minTPos, middleTPos));
        todo.push_back(TodoItem(2 * kPos + 2, rightMiddleTPos, maxTPos));

        // Set an inner node here
        m_tree.push_back(TreeNode(axisValue, 0));

    } else {
        // Place triangles here
        m_tree.push_back(TreeNode(NAN, size));
    }
  }

  // Post-processing step where we replace each value in the tree
  // by the sum of all previous values and itself.
  int sumTreeIndex = 0;
  for (unsigned int i = 0; i < m_tree.size(); i++) {
      sumTreeIndex += m_tree[i].treeIndex;
//      std::cout << i << " " << m_tree[i].treeIndex << " " << sumTreeIndex << std::endl;
      m_tree[i].treeIndex = sumTreeIndex;
  }

  // Compute bounding box for whole tree
  float minX = INFINITY, minY = INFINITY, minZ = INFINITY, maxX = -INFINITY, maxY = -INFINITY, maxZ = -INFINITY;

  for (typename std::vector<Triangle*>::iterator t = m_triangles.begin(); t != m_triangles.end(); t++) {
      int x = (*t)->vertices[0].x;
      int y = (*t)->vertices[0].y;
      int z = (*t)->vertices[0].z;

      if (x < minX) minX = x;
      else if (x > maxX) maxX = x;

      if (y < minY) minY = y;
      else if (y > maxY) maxY = y;

      if (z < minZ) minZ = z;
      else if (z > maxZ) maxZ = z;
  }

  glm::vec3 min = glm::vec3(minX, minY, minZ);
  glm::vec3 max = glm::vec3(maxX, maxY, maxZ);
  m_bBox = new BBox(min, max);

  // Compute bounding sphere (better for intersection test)
  glm::vec3 center = (min + max) / 2.0f;
  float radius = glm::distance(max, center);
  m_bSphere = new BSphere(center, radius);

//  std::cout << "BBox-Min: " << minX << ", " << minY << ", " << minZ << std::endl;
//  std::cout << "BBox-Max: " << maxX << ", " << maxY << ", " << maxZ << std::endl;
//  std::cout << "BSphere: " << center.x << ", " << center.y << ", " << center.z << ": " << radius << std::endl;
}

bool ImplicitKDTree::intersect(Circle& circle, std::list<Triangle*>& hits) {
  BBox circleBox = circle.computeBoundingBox();
  return intersectRec(circle, hits, circleBox, 0, 0);
}

bool ImplicitKDTree::intersectRec(Circle& circle, std::list<Triangle*>& hits, BBox& curBox, int depth, unsigned int kPos) {
  if (curBox.intersects(m_bBox)) {
      TreeNode node = m_tree[kPos];
      TreeNode* prevNode;
      int elementsAtNode = 0;

      // Only look at previous node if kPos != 0 to avoid segfaults
      if (kPos > 0 && kPos < m_tree.size()) {
        prevNode = &m_tree[kPos - 1];
        elementsAtNode = node.treeIndex - prevNode->treeIndex;
      }

      // Check whether the current node is an inner node
      if (elementsAtNode == 0) {
          // Inner node
          int axis = depth % 3;
          BBox* boxes = curBox.split(axis, node.axisValue);

          // Compute child nodes
          unsigned int leftChild = 2 * kPos + 1;
          unsigned int rightChild = leftChild + 1;

          // If the kPos value is still valid, continue with respective child node
          bool intersectA = leftChild < m_tree.size() ? intersectRec(circle, hits, boxes[0], depth + 1, leftChild) : false;
          bool intersectB = rightChild < m_tree.size() ? intersectRec(circle, hits, boxes[1], depth + 1, rightChild) : false;

          return (intersectA || intersectB);
      } else {
          // Leaf node
          typename std::vector<Triangle*>::iterator pos = m_triangles.begin() + prevNode->treeIndex;
          typename std::vector<Triangle*>::iterator end = m_triangles.begin() + node.treeIndex;
          bool hit = false;
          for (; pos != end; pos++) {
              Triangle triangle = **pos;
              if (circle.intersect(triangle)) {
                  hits.push_back(*pos);
                  hit = true;
              }
          }
          return hit;
      }
  } else {
//      std::cout << "Exiting at depth: " << depth << std::endl;
//      std::cout << "curBox-Min: " << curBox.getMin()->x << ", " << curBox.getMin()->y << ", " << curBox.getMin()->z << std::endl;
//      std::cout << "curBox-Max: " << curBox.getMax()->x << ", " << curBox.getMax()->y << ", " << curBox.getMax()->z << std::endl;

//      std::cout << "m_bBox-Min: " << m_bBox->getMin()->x << ", " << m_bBox->getMin()->y << ", " << m_bBox->getMin()->z << std::endl;
//      std::cout << "m_bBox-Max: " << m_bBox->getMax()->x << ", " << m_bBox->getMax()->y << ", " << m_bBox->getMax()->z << std::endl;
      return false;
  }
}
