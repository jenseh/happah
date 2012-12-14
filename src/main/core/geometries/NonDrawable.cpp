#include "NonDrawable.h"


void NonDrawable::dataPushback(glm::vec4 data) {
    vertexData_.push_back(data);
}


QuadMesh* NonDrawable::toQuadMesh() {
    QuadMesh* mesh = new QuadMesh(vertexData_);
    if (getName() != "") {
        mesh->setName(getName() + " - Instance 1");
    }
    return mesh;
}
