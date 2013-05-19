#ifndef FASTKDTREE_H
#define FASTKDTREE_H

#include "TriangleIterator.h"

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

    /**
     * @brief sort mergesort the triangles (see more http://de.wikipedia.org/wiki/Mergesort)
     * @param begin the iterator to iterate over the triangles
     * @param end the end element to have a stop element for the begin iterator
     */
    void sort(TriangleIterator* begin, TriangleIterator* end);

    /**
     * @brief merge merge the two list into each other
     * @param frist_begin the frist list start
     * @param frist_end the first list end
     * @param second_begin the second list start
     * @param second_end the second list end
     */
    void merge(TriangleIterator* first_begin, TriangleIterator* first_end,
          TriangleIterator* second_begin, TriangleIterator* second_end);

    /**
     * @brief switchPointers switch the both pointers via a so called 'Ringtausch'
     * TODO: Xor binary switch without a temporary variable possible
     * @param first the first pointer
     * @param second the second pointer
     */
    void switchPointers(TriangleVerticeRefs* first, TriangleVerticeRefs* second);

public:
    /**
     * @brief The constructor builds up the whole fast kd-tree.
     * @param begin the start of the iterator to the triangles
     * @param end the end index to the triangle iterator
     * @param depth saves the depth for each step
     */
    FastKdTree(TriangleIterator* begin, TriangleIterator* end, int depth = 0);

    /**
      * @brief destroys the pointer to the child.
      */
    ~FastKdTree();

};

#endif // FASTKDTREE_H
