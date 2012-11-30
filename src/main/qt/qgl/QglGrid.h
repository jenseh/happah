#ifndef GRID_H
#define GRID_H

#include "QglGeometryObject.h"

class QglGrid: public QglGeometryObject {
public:
    QglGrid();
	void createVertexData();
    void draw(QGLShaderProgram *shader, QMatrix4x4* projectionMatrix = 0, QMatrix4x4* viewMatrix = 0, QVector3D* cameraPosition = 0);
    
	QRectF boundingRect() const;// DO NOT CHANGE INTO getBoundingRect as bounding Rectangle implements a virtual function of component.
};

#endif // GRID_H
