#ifndef TRIANGLEMESH_H
#define TRIANGLEMESH_H

#include <vector>
#include <glm/glm.hpp>

#include "../geometries/GeometryObject.h"

class TriangleMesh : public GeometryObject
{
public:
    TriangleMesh(std::vector<glm::vec4> vertexData);

    std::vector<glm::vec4> getVertexData();

protected:
    std::vector<glm::vec4> vertexData_;
};

#endif // TRIANGLEMESH_H
