#ifndef TRIANGLEMESH_H
#define TRIANGLEMESH_H

#include <vector>
#include <glm/glm.hpp>
#include "../primitives/Triangle.h"
#include "Drawable.h"
#include "../../gui/gl/DrawManager.h"
#include "../primitives/Ray.h"
#include "RayCloud.h"


class TriangleMesh : public Drawable
{
public:
    std::vector<Triangle> triangles_;

    TriangleMesh(std::vector<glm::vec4> vertexData);
    ~TriangleMesh();

    std::vector<glm::vec4>* getVertexData();
    int getTupleSize();
    RayCloud* toRayCloud();

    void fillTriangles();

protected:
    std::vector<glm::vec4> vertexData_;
};

#endif // TRIANGLEMESH_H
