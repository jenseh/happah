#include "Grid.h"

Grid::Grid(QMatrix4x4 *_projectionMatrix,QMatrix4x4 *_viewMatrix,QVector3D* _camPos):GeometryObject(_projectionMatrix,_viewMatrix,_camPos)
{
}


void Grid::draw(QGLShaderProgram *shader) {
        BindVBuffer();
        shader->bind();
        shader->setAttributeBuffer("vertex", GL_FLOAT, 0, 4, 0);
        shader->enableAttributeArray("vertex");
        shader->setUniformValue("MVP", MVP);

        int mode = GL_LINES;
        int stride = 0;
        glDrawArrays(mode, stride, vertexData.size());

        shader->release();
}

void Grid::CreateVertexData(){
    for (float x = -2.0; x <= 2.0; x = x + 0.5f) {
        for (float z = -2.0f; z <= 2.0f; z = z + 0.5f) {
            vertexData.push_back(glm::vec4(x, -1.0f, -2.0, 1.0f));
            vertexData.push_back(glm::vec4(x, -1.0f, 2.0, 1.0f));
            vertexData.push_back(glm::vec4(-2.0f, -1.0f, z, 1.0f));
            vertexData.push_back(glm::vec4(2.0f, -1.0f, z, 1.0f));
        }
    }
}
