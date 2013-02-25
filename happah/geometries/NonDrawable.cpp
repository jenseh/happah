#include "NonDrawable.h"

NonDrawable::NonDrawable(std::string name) : GeometryObject(name) {}

NonDrawable::~NonDrawable() {}

QuadMesh* NonDrawable::toQuadMesh() {} //TODO: As written in header, this method shouldn't exist or should be realised in another way!
TriangleMesh* NonDrawable::toTriangleMesh() {}
glm::vec3 NonDrawable::getControlPoint(int index){}
void NonDrawable::setControlPoint(int index,glm::vec3 value){}
