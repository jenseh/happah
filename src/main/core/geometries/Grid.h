#ifndef GRID_H
#define GRID_H

#include "NonDrawable.h"

class Grid : public NonDrawable
{
public:
    Grid();
    ~Grid();

    virtual void createVertexData();
};

#endif // GRID_H
