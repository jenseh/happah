#ifndef FASTKDTREE_H
#define FASTKDTREE_H

#include "TriangleIterator.h"
/**
 * @brief The FastKdTree class
 */
class FastKdTree {
public:
    /**
     * @brief FastKdTree
     * @param begin
     * @param end
     */
    FastKdTree(TriangleIterator& begin, TriangleIterator& end);

    /**
     * @brief intersectAll
     * @return
     */
    bool intersectAll();

    /**
     * @brief intersectFirst
     * @return
     */
    hpreal intersectFirst();

    FastKdTree* leftChild();

    FastKdTree* rightChild();

    bool isLeaf();
};

#endif // FASTKDTREE_H
