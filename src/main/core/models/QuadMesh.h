#ifndef QUADMESH_H
#define QUADMESH_H

#include <vector>
#include <glm/glm.hpp>

#include "Drawable.h"
#include "../DrawManager.h"

class QuadMesh : public Drawable {

public:
    QuadMesh(std::vector<glm::vec4> vertexData);
    ~QuadMesh();

    std::vector<glm::vec4>* getVertexData();

protected:
    std::vector<glm::vec4> vertexData_;
};

#endif // QUADMESH_H
