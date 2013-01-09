#ifndef DRAWMANAGERITEM_H
#define DRAWMANAGERITEM_H

#include <QGLShaderProgram>
#include <QGLBuffer>
#include "../../core/models/Drawable.h"

class DrawManagerItem {
public:
	DrawManagerItem(Drawable* drawable, int offset);

	void draw(QGLBuffer* buffer, QGLShaderProgram* shader,
			QMatrix4x4* projectionMatrix, QMatrix4x4* viewMatrix,
			QVector3D* cameraPosition);
	Drawable* getDrawable();
	int getOffset();
private:
	Drawable* drawable_;
	int offset_;
	QGLBuffer colorBuffer_;
};

#endif // DRAWMANAGERITEM_H
