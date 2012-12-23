#ifndef DRAWMANAGERITEM_H
#define DRAWMANAGERITEM_H

#include <QGLShaderProgram>
#include <QGLBuffer>
#include "models/Drawable.h"

class DrawManagerItem {
public:
	DrawManagerItem(Drawable* drawable, int offset);

	void draw(QGLBuffer* buffer, QGLShaderProgram* shader, QMatrix4x4* projectionMatrix,
		  QMatrix4x4* viewMatrix, QVector3D* cameraPosition);

private:
	Drawable* drawable_;
	int offset_;
};

#endif // DRAWMANAGERITEM_H
