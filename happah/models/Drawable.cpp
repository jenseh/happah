#include "happah/models/Drawable.h"

Drawable::Drawable(std::string name) : GeometryObject(name) {}

Drawable::~Drawable() {}

void Drawable::setColorData(std::vector<Color>& colorData){
    m_colorData = colorData;
}

void Drawable::setColor(hpreal red, hpreal green, hpreal blue, hpreal alpha) {
	for(uint i = 0; i < (getVertexData()->size()/2); i++){
		Color color = {red, green, blue, alpha};
		m_colorData.push_back(color);
	}
}

std::vector<Color>* Drawable::getColorData(){
	return &m_colorData;
}

bool Drawable::hasColorData() {
	return m_colorData.size() != 0;
}

Material Drawable::getMaterial(){
	return m_material;
}

void Drawable::setMaterial(float ka, float kd, float ks, float shininess){
	m_material.setAmbientFactor(ka);
	m_material.setDiffuseFactor(kd);
	m_material.setSpecularFactor(ks);
	m_material.setPhongExponent(shininess);
}
