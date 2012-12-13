#ifndef NONDRAWABLE_H
#define NONDRAWABLE_H

#include "GeometryObject.h"
#include "../models/QuadMesh.h"

class NonDrawable : public GeometryObject
{
public:
    NonDrawable();


    void createVertexData();
    void dataPushback(glm::vec4 data);
    QuadMesh* toQuadMesh();

    std::vector<glm::vec4> vertexData_;
};

#endif // NONDRAWABLE_H
