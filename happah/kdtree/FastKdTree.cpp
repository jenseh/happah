#include "FastKdTree.h"

FastKdTree::FastKdTree(TriangleIterator* begin, TriangleIterator* end, int depth) {
    leftChild = NULL;
    rightChild = NULL;

    if (depth == 0) {
        sort(begin, end);
    }

}

FastKdTree::~FastKdTree() {
    delete leftChild;
    delete rightChild;
}

void FastKdTree::sort(TriangleIterator* begin, TriangleIterator* end) {
    if (begin != end) {
        //get the length of the list
        int n = 0;
        while (begin->operator [](n) != end->operator [](0)) {
            n++;
        }

        // if list has only one piece, no need to mergesort again
        if (n > 0) {
            sort(begin, begin + n * sizeof(TriangleVerticeRefs*) /2);
            sort(begin + (n+1) * sizeof(TriangleVerticeRefs*) /2, end);
            merge(begin,
                  begin + n * sizeof(TriangleVerticeRefs*) /2,
                  begin + (n+1) * sizeof(TriangleVerticeRefs*) /2,
                  end);
        }
    }
}

void FastKdTree::merge(TriangleIterator* first_begin, TriangleIterator* first_end,
                  TriangleIterator* second_begin, TriangleIterator* second_end) {
    int indexFront = 0, indexBack = 0;
    while (first_begin->operator [](indexFront) != first_end->operator [](0)
           && second_begin->operator [](indexBack) != second_end->operator [](0)) {

        // second list item is lower x
        if (second_begin->operator [](indexBack)->vertices[0]->x
            < first_begin->operator [](indexFront)->vertices[0]->x) {
            switchPointers(second_begin->operator [](indexBack), first_begin->operator [](indexFront));
            indexFront++;
        }

        /***********************************************************************************/
        //TODO: OTHER CASES FOR ALGORITHM
        /***********************************************************************************/

    }
}

void FastKdTree::switchPointers(TriangleVerticeRefs* first, TriangleVerticeRefs* second) {
    TriangleVerticeRefs* tmp = first;
    first = second;
    second = tmp;
}
