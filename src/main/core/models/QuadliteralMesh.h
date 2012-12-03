#ifndef QUADLITERALMESH_H
#define QUADLITERALMESH_H

#include "Model.h"
#include <vector>
#include <glm/glm.hpp>


class QuadliteralMesh: public Model{

public:
    QuadliteralMesh(std::vector<glm::vec4> vertexData);

    std::vector<glm::vec4> getVertexData();

protected:
    std::vector<glm::vec4> vertexData_;
};

#endif // QUADLITERALMESH_H
