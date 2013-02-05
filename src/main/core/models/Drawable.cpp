#include "Drawable.h"

Drawable::Drawable(std::string name) : GeometryObject(name) {}

Drawable::~Drawable() {}


std::vector<glm::vec4>* Drawable::getVertexData() {}
int Drawable::getTupleSize() {}

void Drawable::setColorData(std::vector<Color>& colorData){
    m_colorData = colorData;
}

std::vector<Color>* Drawable::getColorData(){
    return &m_colorData;
}

Material Drawable::getMaterial(){
  return m_material;
}

void Drawable::setMaterial(float ka, float kd, float ks, float shininess){
  m_material.m_ka = ka;
  m_material.m_kd = kd;
  m_material.m_ks= ks;
  m_material.m_shininess = shininess;
}