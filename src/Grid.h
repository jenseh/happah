#ifndef GRID_H
#define GRID_H

#include "GeometryObject.h"

class Grid: public GeometryObject {
public:
    Grid(QMatrix4x4* projectionMatrix = 0, QMatrix4x4 *viewMatrix = 0,
            QVector3D* camPos = 0);
	void createVertexData();
	void draw(QGLShaderProgram *shader);
};

#endif // GRID_H
