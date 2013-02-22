#include "Material.h"
#include <glm/glm.hpp>

Material::Material()
{
  m_ka = 1.0f;
  m_kd = 1.0f;
  m_ks = 1.0f;
  m_shininess = 20.0f;
}

void Material::setKa(float ka){
  m_ka = ka;
}

void Material::setKd(float kd){
  m_kd = kd;
}

void Material::setKs(float ks){
  m_ks = ks;
}

void Material::setShininess(float shininess){
  m_shininess = shininess;
}

float Material::getKa(){
  return m_ka;
}

float Material::getKd(){
  return m_kd;
}

float Material::getKs(){
  return m_ks;
}

float Material::getShininess(){
  return m_shininess;
}
