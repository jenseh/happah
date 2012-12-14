#ifndef NONDRAWABLE_H
#define NONDRAWABLE_H

#include "GeometryObject.h"
#include "../models/QuadMesh.h"

class NonDrawable : public GeometryObject
{
protected:
	std::vector<glm::vec4> vertexData_;
public:
	virtual void createVertexData() = 0;
    void dataPushback(glm::vec4 data);
    QuadMesh* toQuadMesh();
};

#endif // NONDRAWABLE_H
