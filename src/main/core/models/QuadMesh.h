#ifndef QUADMESH_H
#define QUADMESH_H

#include <vector>
#include <glm/glm.hpp>

#include "../geometries/GeometryObject.h"

class QuadMesh : public GeometryObject {

public:
    QuadMesh(std::vector<glm::vec4> vertexData);

    std::vector<glm::vec4> getVertexData();

protected:
    std::vector<glm::vec4> vertexData_;
};

#endif // QUADMESH_H
