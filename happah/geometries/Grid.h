#ifndef GRID_H
#define GRID_H

#include "happah/geometries/NonDrawable.h"
#include "happah/geometries/QuadMesh.h"

class Grid : public NonDrawable
{
public:
    Grid(std::string name = "Grid");
    ~Grid();

    QuadMesh* toQuadMesh();
    TriangleMesh* toTriangleMesh();

private:
    std::vector<glm::vec4> m_vertexData;
};

#endif // GRID_H
