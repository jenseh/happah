#include "Drawable.h"

Drawable::~Drawable() {}


std::vector<glm::vec4>* Drawable::getVertexData() {}
int Drawable::getTupleSize() {}

void Drawable::setColorData(std::vector<Color>& colorData){
    colorData_ = colorData;
}

std::vector<Color>* Drawable::getColorData(){
    return &colorData_;
}
