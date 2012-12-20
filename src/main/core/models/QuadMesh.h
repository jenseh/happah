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

    std::vector<glm::vec4> getVertexData();
    void draw(DrawManager* drawManager);

protected:
    std::vector<glm::vec4> vertexData_;
};

#endif // QUADMESH_H
