#ifndef GRID_H
#define GRID_H

#include "GeometryObject.h"

class Grid: public GeometryObject {
public:
	Grid(QMatrix4x4 *_projectionMatrix = 0, QMatrix4x4 *_viewMatrix = 0,
			QVector3D* _camPos = 0);
	void createVertexData();
	void draw(QGLShaderProgram *shader);
};

#endif // GRID_H
