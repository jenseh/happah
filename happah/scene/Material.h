#ifndef MATERIAL_H
#define MATERIAL_H

#include <glm/glm.hpp>

class Material
{
public:
  Material();
  void setAmbientFactor(float ambientFactor);
  void setDiffuseFactor(float diffuseFactor);
  void setSpecularFactor(float specularFactor);
  void setPhongExponent(float phongExponent);

  float getAmbientFactor();
  float getDiffuseFactor();
  float getSpecularFactor();
  float getPhongExponent();
private:
  float m_ambientFactor;
  float m_diffuseFactor;
  float m_specularFactor;
  float m_phongExponent;
};

#endif // MATERIAL_H
