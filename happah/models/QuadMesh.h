#ifndef QUADMESH_H
#define QUADMESH_H

#include <glm/glm.hpp>
#include <vector>

#include "happah/HappahTypes.h"
#include "happah/models/Drawable.h"
#include "happah/models/TriangleMesh.h"
#include "happah/primitives/Color.h"

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
