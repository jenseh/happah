#ifndef FASTKDTREE_H
#define FASTKDTREE_H

#include <list>
#include <iostream>

#include "TriangleIterator.h"
#include "happah/math/Circle.h"
#include "happah/math/Ray.h"
#include "happah/kdtree/BBox.h"

/**
 * @brief The class is used to build a fast kd tree. Only the really
 * needed elements are inside this class. The class has as right and
 * left children this same class
 */
class FastKdTree {

private:
    /**
     * @brief the left lower kd-tree
     */
    FastKdTree* leftChild;

    /**
     * @brief the right lower kd-tree
     */
    FastKdTree* rightChild;

public:
    /**
     * @brief The constructor builds up the whole fast kd-tree.
     * @param begin the start of the iterator to the triangles
     * @param end the end index to the triangle iterator
     */
    FastKdTree(TriangleIterator begin, TriangleIterator end);

    /**
      * @brief destroys the pointer to the child.
      */
    ~FastKdTree();
};

#endif // FASTKDTREE_H
