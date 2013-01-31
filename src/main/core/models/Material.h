#ifndef MATERIAL_H
#define MATERIAL_H
#include <glm/glm.hpp>

class Material
{
public:
  Material();
  float m_ka;
  float m_kd;
  float m_ks;
  float m_shininess;   // phong exponent
};

#endif // MATERIAL_H
