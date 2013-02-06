#ifndef QUADMESH_H
#define QUADMESH_H

#include <vector>
#include <glm/glm.hpp>

#include "Drawable.h"
#include "TriangleMesh.h"
#include "../../gui/gl/DrawManager.h"
#include "../primitives/Color.h"
#include "../../HappahTypes.h"

class QuadMesh : public Drawable {

public:
    QuadMesh(std::vector<glm::vec4> vertexData, std::string name);
    ~QuadMesh();

    std::vector<glm::vec4>* getVertexData();
    int getTupleSize();

    TriangleMesh* toTriangleMesh();


protected:
    std::vector<glm::vec4> m_vertexData;
};

#endif // QUADMESH_H