#ifndef DRAWABLE_H
#define DRAWABLE_H

#include "../geometries/GeometryObject.h"

class Drawable : public GeometryObject{
public:
    virtual ~Drawable();

    virtual std::vector<glm::vec4>* getVertexData();
};

#endif // DRAWABLE_H
