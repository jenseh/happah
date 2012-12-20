#ifndef GRID_H
#define GRID_H

#include "NonDrawable.h"
#include "../models/QuadMesh.h"

class Grid : public NonDrawable
{
public:
    Grid();
    ~Grid();

    QuadMesh* toQuadMesh();
    TriangleMesh* toTriangleMesh();

private:
    std::vector<glm::vec4> vertexData_;
};

#endif // GRID_H
