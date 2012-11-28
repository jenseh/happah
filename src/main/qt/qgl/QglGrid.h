#ifndef GRID_H
#define GRID_H

#include "QglGeometryObject.h"

class Grid: public GeometryObject {
public:
    Grid(QMatrix4x4* projectionMatrix = 0, QMatrix4x4 *viewMatrix = 0,
            QVector3D* camPos = 0);
	void createVertexData();
	void draw(QGLShaderProgram *shader);
	QRectF boundingRect() const;				// DO NOT CHANGE INTO getBoundingRect as bounding Rectangle implements a virtual function of component.
};

#endif // GRID_H
