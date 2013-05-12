#ifndef TRIANGLEITERATOR_H
#define TRIANGLEITERATOR_H

#include "happah/math/TriangleVerticeRefs.h"
#include <iterator>

using namespace std;

/**
 * @brief The abstract trinalgle iterator class which inherits from the C++ iterator structure
 *  Here we use a random_access_iterator to iterator over the structure.
 */
class TriangleIterator : public iterator<random_access_iterator_tag, TriangleVerticeRefs> {

public:
    /**
     * @brief operator [] the subclasses have to overload the [] operator to get access to the single triangles
     * @return a single triangle - within are just the references to the vertices
     */
    virtual TriangleVerticeRefs* operator[](int) = 0;

};

#endif // TRIANGLEITERATOR_H
