#ifndef GRID_H
#define GRID_H

#include "GeometryObject.h"

class Grid : public GeometryObject
{
public:
    Grid();
    ~Grid();

    void createVertexData();
};

#endif // GRID_H
