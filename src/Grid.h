#ifndef GRID_H
#define GRID_H

#include "GeometryObject.h"

class Grid : public GeometryObject
{
public:
    Grid();
    void CreateVertexData();
    void draw(QGLShaderProgram *shader);
};

#endif // GRID_H
