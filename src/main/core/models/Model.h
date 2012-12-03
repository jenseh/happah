#ifndef MODEL_H
#define MODEL_H

#include <QMatrix4x4>

class Model
{
public:
    Model();
    ~Model();

    // Transformations
    void rotate(float angle, float x, float y, float z);
    void translate(float x, float y, float z);
    void scale(float x, float y, float z);

protected:
    QMatrix4x4 modelMatrix_;
};

#endif // MODEL_H
