#ifndef NONDRAWABLE_H
#define NONDRAWABLE_H

#include "GeometryObject.h"
#include "../models/QuadMesh.h"
#include "../models/TriangleMesh.h"

class NonDrawable : public GeometryObject
{
public:
    NonDrawable(std::string name);
    virtual ~NonDrawable();
    virtual QuadMesh* toQuadMesh(); //TODO: We have to do something else here. We use this method like it was an "abstract" one, but do really all "NonDrawables" need a toQuadMesh() method???
    virtual TriangleMesh* toTriangleMesh() = 0;
};

#endif // NONDRAWABLE_H
