#ifndef DRAWABLE_H
#define DRAWABLE_H

#include <glm/glm.hpp>
#include "../geometries/GeometryObject.h"
#include "Material.h"

class Drawable : public GeometryObject{

public:
    Drawable(std::string name);
    virtual ~Drawable();

    virtual std::vector<glm::vec4>* getVertexData() = 0;
    virtual int getTupleSize() = 0;

    void setColorData(std::vector<Color>& colorData);
    std::vector<Color>* getColorData();
    bool hasColorData();
    Material getMaterial();
    void setMaterial(float ka,float kd,float ks,float shininess);

private:
    std::vector<Color> m_colorData;
    Material m_material;
};

#endif // DRAWABLE_H
