#ifndef DRAWABLE_H
#define DRAWABLE_H

#include <glm/glm.hpp>

#include "happah/HappahTypes.h"
#include "happah/geometries/GeometryObject.h"
#include "happah/scene/Material.h"

class Drawable : public GeometryObject{

public:
    Drawable(std::string name);
    virtual ~Drawable();

    virtual std::vector<glm::vec4>* getVertexData() = 0;
//    virtual void setVertexData(std::vector<glm::vec4>*) = 0;
    virtual int getTupleSize() = 0;

    void setColorData(std::vector<Color>& colorData);
    void setColor(hpreal red, hpreal green, hpreal blue, hpreal alpha);
    std::vector<Color>* getColorData();
    bool hasColorData();
    Material getMaterial();
    void setMaterial(float ka,float kd,float ks,float shininess);

protected:
    std::vector<Color> m_colorData;
    Material m_material;
};

#endif // DRAWABLE_H
