#ifndef NONDRAWABLE_H
#define NONDRAWABLE_H

#include "GeometryObject.h"
#include "../models/QuadMesh.h"
#include "../models/TriangleMesh.h"

class NonDrawable : public GeometryObject
{
public:
    virtual ~NonDrawable();
    virtual QuadMesh* toQuadMesh();
    virtual TriangleMesh* toTriangleMesh();
};

#endif // NONDRAWABLE_H
