#ifndef TRIANGLEMESH_H
#define TRIANGLEMESH_H

#include <vector>
#include <glm/glm.hpp>

#include "Drawable.h"
#include "../DrawManager.h"

class TriangleMesh : public Drawable
{
public:
    TriangleMesh(std::vector<glm::vec4> vertexData);
    ~TriangleMesh();

    std::vector<glm::vec4>* getVertexData();

protected:
    std::vector<glm::vec4> vertexData_;
};

#endif // TRIANGLEMESH_H
