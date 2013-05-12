#ifndef TRIANGLEVERTICEREFS_H
#define TRIANGLEVERTICEREFS_H

/**
 * @brief The TriangleVerticeRefs struct to store the vertices references to one complete triangle
 */
struct TriangleVerticeRefs {
    /**
     * @brief all the references to the 3 vertices
     */
    const hpvec3* vertices[3];

    /**
     * @brief Triangle constructor create one TriangleVerticeRefs type
     */
    TriangleVerticeRefs(const hpvec3* vertexA, const hpvec3* vertexB, const hpvec3* vertexC) {
      vertices[0] = vertexA;
      vertices[1] = vertexB;
      vertices[2] = vertexC;
    }

    ~TriangleVerticeRefs() {}
};

#endif // TRIANGLEVERTICEREFS_H
