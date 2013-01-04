#ifndef TRIANGLEMESH_H
#define TRIANGLEMESH_H

#include <vector>
#include <glm/glm.hpp>
#include "../geometries/Triangle.h"
#include "Drawable.h"
#include "../../gui/gl/DrawManager.h"
#include "../geometries/Ray.h"


class TriangleMesh : public Drawable
{
public:
    std::vector<Triangle> triangles_;

    TriangleMesh(std::vector<glm::vec4> vertexData);
    ~TriangleMesh();

    std::vector<glm::vec4>* getVertexData();
    int getTupleSize();
    std::vector<Ray*> toRayCloud();

    void fillTriangles();

protected:
    std::vector<glm::vec4> vertexData_;
};

#endif // TRIANGLEMESH_H
