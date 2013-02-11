#ifndef TRIANGLEMESH_H
#define TRIANGLEMESH_H

#include <vector>
#include <glm/glm.hpp>

#include "../primitives/Triangle.h"
#include "Drawable.h"
#include "../primitives/Ray.h"
#include "../primitives/Color.h"
#include "RayCloud.h"


class TriangleMesh : public Drawable
{
public:

    TriangleMesh(std::vector<glm::vec4> *vertexData, std::string name);
    ~TriangleMesh();
    TriangleMesh& operator=(const TriangleMesh& other);


    std::vector<glm::vec4>* getVertexData();
    int getTupleSize();
    std::vector<Triangle*>* getTriangles();

    RayCloud* toRayCloud();

    void fillTriangles();

protected:
    std::vector<glm::vec4> *m_vertexData;
    std::vector<Triangle*> m_triangles;
};

#endif // TRIANGLEMESH_H