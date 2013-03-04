#ifndef NONDRAWABLE_H
#define NONDRAWABLE_H

#include "happah/geometries/GeometryObject.h"
#include "happah/geometries/QuadMesh.h"
#include "happah/geometries/TriangleMesh.h"

class NonDrawable : public GeometryObject
{
public:
    NonDrawable(std::string name);
    virtual ~NonDrawable();
    virtual QuadMesh* toQuadMesh(); //TODO: We have to do something else here. We use this method like it was an "abstract" one, but do really all "NonDrawables" need a toQuadMesh() method???
    virtual TriangleMesh* toTriangleMesh();
    virtual glm::vec3 getControlPoint(int index);
    virtual void setControlPoint(int index,glm::vec3 value);
};

#endif // NONDRAWABLE_H
