#ifndef MATERIAL_H
#define MATERIAL_H

#include <glm/glm.hpp>

class Material
{
public:
  Material();
  void setKa(float ka);
  void setKd(float kd);
  void setKs(float ks);
  void setShininess(float shininess);

  float getKa();
  float getKd();
  float getKs();
  float getShininess();
private:
  float m_ka;
  float m_kd;
  float m_ks;
  float m_shininess;   // phong exponent
};

#endif // MATERIAL_H
