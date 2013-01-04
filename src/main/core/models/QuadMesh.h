#ifndef QUADMESH_H
#define QUADMESH_H

#include <vector>
#include <glm/glm.hpp>

#include "Drawable.h"
#include "TriangleMesh.h"
#include "../../gui/gl/DrawManager.h"

class QuadMesh : public Drawable {

public:
    QuadMesh(std::vector<glm::vec4> vertexData);
    ~QuadMesh();

    std::vector<glm::vec4>* getVertexData();
    int getTupleSize();

    TriangleMesh* toTriangleMesh();

protected:
    std::vector<glm::vec4> vertexData_;
};

#endif // QUADMESH_H
