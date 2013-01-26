#include "Drawable.h"

Drawable::~Drawable() {}


std::vector<glm::vec4>* Drawable::getVertexData() {}
int Drawable::getTupleSize() {}

void Drawable::setColorData(std::vector<Color>& colorData){
    m_colorData = colorData;
}

std::vector<Color>* Drawable::getColorData(){
    return &m_colorData;
}
