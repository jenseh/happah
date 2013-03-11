#ifndef WORM_H
#define WORM_H

#include <cmath>
#include <glm/glm.hpp>

#include "happah/geometries/Geometry.h"
#include "happah/HappahTypes.h"
#include "happah/geometries/Mesh.h"
#include "happah/geometries/StandardProfile.h"
#include "happah/LoggingUtils.h"


class Worm : public Geometry {
public:
  Worm(hpuint toothCount = 4,
      hpreal module = 0.2 * M_PI,
      hpreal pressureAngle = 20.0 / 360.0 * 2.0 * M_PI,
      hpuint rotations = 2);
      
  ~Worm();
  
  std::vector<hpvec3>* createVertexData();
  
  TriangleMesh* toTriangleMesh();
  
private:
  hpuint m_toothCount;
  hpreal m_module;
  hpreal m_pressureAngle;
  hpuint m_rotations;
  
  hpreal m_radius;
};

#endif // WORM_H
