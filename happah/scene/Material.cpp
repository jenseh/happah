#include <glm/glm.hpp>

#include "happah/scene/Material.h"

Material::Material()
{
  m_ambientFactor = 1.0f;
  m_diffuseFactor = 1.0f;
  m_specularFactor = 1.0f;
  m_phongExponent = 20.0f;
}

void Material::setAmbientFactor(float ambientFactor){
  m_ambientFactor = ambientFactor;
}

void Material::setDiffuseFactor(float diffuseFactor){
  m_diffuseFactor = diffuseFactor;
}

void Material::setSpecularFactor(float specularFactor){
  m_specularFactor = specularFactor;
}

void Material::setPhongExponent(float phongExponent){
  m_phongExponent = phongExponent;
}

float Material::getAmbientFactor(){
  return m_ambientFactor;
}

float Material::getDiffuseFactor(){
  return m_diffuseFactor;
}

float Material::getSpecularFactor(){
  return m_specularFactor;
}

float Material::getPhongExponent(){
  return m_phongExponent;
}
