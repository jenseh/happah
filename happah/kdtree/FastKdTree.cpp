#include "FastKdTree.h"

FastKdTree::FastKdTree(TriangleIterator* begin, TriangleIterator* end) {
    leftChild = NULL;
    rightChild = NULL;
}

FastKdTree::~FastKdTree() {
    delete leftChild;
    delete rightChild;
}

