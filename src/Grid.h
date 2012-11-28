#ifndef GRID_H
#define GRID_H

#include "GeometryObject.h"

class Grid: public GeometryObject {
public:
    Grid();
	void createVertexData();
    void draw(QGLShaderProgram *shader, QMatrix4x4* projectionMatrix,
              QMatrix4x4* viewMatrix, QVector3D* cameraPosition);
	QRectF boundingRect() const;				// DO NOT CHANGE INTO getBoundingRect as bounding Rectangle implements a virtual function of component.
};

#endif // GRID_H
