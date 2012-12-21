#ifndef NONDRAWABLE_H
#define NONDRAWABLE_H

#include "GeometryObject.h"
#include "../models/QuadMesh.h"
#include "../models/TriangleMesh.h"

class NonDrawable : public GeometryObject
{
public:
    virtual ~NonDrawable();
    virtual QuadMesh* toQuadMesh() = 0;
    virtual TriangleMesh* toTriangleMesh() = 0;
};

#endif // NONDRAWABLE_H
