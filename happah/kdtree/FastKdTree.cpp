
#include "FastKdTree.h"


FastKdTree::FastKdTree(TriangleIterator begin, TriangleIterator end) {

}

FastKdTree::~FastKdTree() {
    delete leftChild;
    delete rightChild;
}
