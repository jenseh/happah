#ifndef DRAWMANAGER_H
#define DRAWMANAGER_H

#include <QGLBuffer>
#include <QGLShaderProgram>
#include "../../core/models/Drawable.h"
#include "DrawManagerItem.h"

class DrawManager {
public:
	DrawManager();

	void draw(QMatrix4x4* projectionMatrix, QMatrix4x4* viewMatrix,
			QVector3D* cameraPosition);
	void addDrawable(Drawable* drawable);
	bool initShaderPrograms();
    int createVertexBuffer();
    int createColorBuffer();

private:
	QGLBuffer* vertexBuffer_;
    QGLBuffer* colorBuffer_;
	std::map<int, DrawManagerItem*> itemMap_;
	QGLShaderProgram* shader_;
	QGLShaderProgram* coordShader_;
    int curVertexBufferOffset;
    int curColorBufferOffset;
};

#endif // DRAWMANAGER_H
