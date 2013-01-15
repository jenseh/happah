#ifndef TRIANGLEMESH_H
#define TRIANGLEMESH_H

#include <vector>
#include <glm/glm.hpp>

#include "../primitives/Triangle.h"
#include "Drawable.h"
#include "../../gui/gl/DrawManager.h"
#include "../primitives/Ray.h"
#include "../primitives/Color.h"
#include "RayCloud.h"


class TriangleMesh : public Drawable
{
public:

    TriangleMesh(std::vector<glm::vec4> vertexData);
    ~TriangleMesh();

    std::vector<glm::vec4>* getVertexData();
    int getTupleSize();
    std::vector<Triangle*>* getTriangles();

    RayCloud* toRayCloud();

    void fillTriangles();

protected:
    std::vector<glm::vec4> vertexData_;
    std::vector<Triangle*> triangles_;
};

#endif // TRIANGLEMESH_H
