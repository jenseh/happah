#ifndef WORM_H
#define WORM_H

#include <glm/glm.hpp>
#include <cmath>

#include "happah/HappahTypes.h"
#include "happah/geometries/Geometry.h"
#include "happah/geometries/Mesh.h"
#include "happah/geometries/StandardProfile.h"
#include "happah/LoggingUtils.h"


class Worm : public Geometry {
public:
  Worm(hpuint toothCount = 16,
      hpreal module = 0.2 * M_PI,
      hpreal pressureAngle = 20.0 / 360.0 * 2.0 * M_PI,
      hpuint rotations = 1);
      
  ~Worm();
  
  std::vector<hpvec3>* createVertexData();
  
  hpreal getToothCount();
  hpreal getModule();
  hpreal getPressureAngle();

  void setToothCount(hpreal toothCount);
  void setModule(hpreal module);
  void setPressureAngle(hpreal pressureAngle);

  TriangleMesh* toTriangleMesh();
  
private:
  hpuint m_toothCount;
  hpreal m_module;
  hpreal m_pressureAngle;
  hpuint m_rotations;
  
  hpreal m_radius;

  StandardProfile* m_standardProfile;

  void updateValues();
};
typedef shared_ptr<Worm> Worm_ptr;

#endif // WORM_H
