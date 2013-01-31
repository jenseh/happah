#include "Material.h"
#include <glm/glm.hpp>

Material::Material()
{
  m_ka = 1.0f;
  m_kd=(1.0f);
  m_ks=(1.0f);
  m_shininess = 20.0f;
}
