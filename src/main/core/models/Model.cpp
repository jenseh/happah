#include "Model.h"

Model::Model()
{
    modelMatrix_.setToIdentity();
}

Model::~Model()
{
}

void Model::rotate(float angle, float x, float y, float z) {
    modelMatrix_.rotate(angle, x, y, z);
}

void Model::translate(float x, float y, float z) {
    modelMatrix_.translate(x, y, z);
}

void Model::scale(float x, float y, float z) {
    modelMatrix_.scale(x, y, z);
}
