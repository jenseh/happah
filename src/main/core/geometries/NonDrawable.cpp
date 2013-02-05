#include "NonDrawable.h"

NonDrawable::NonDrawable(std::string name) : GeometryObject(name) {}

NonDrawable::~NonDrawable() {}

QuadMesh* NonDrawable::toQuadMesh() {}
TriangleMesh* NonDrawable::toTriangleMesh() {}
