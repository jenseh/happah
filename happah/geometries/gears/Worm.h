#ifndef WORM_H
#define WORM_H

#include <glm/glm.hpp>
#include <cmath>
#include <memory>

#include "happah/HappahTypes.h"
#include "happah/geometries/Geometry.h"
#include "happah/geometries/gears/StandardProfile.h"
#include "happah/geometries/ZCircleCloud.h"
#include "happah/geometries/TriangleMesh.h"
#include "happah/LoggingUtils.h"


class Worm : public Geometry {
public:
  Worm(hpuint toothCount = 2,
      hpreal module = 0.13,
      hpreal pressureAngle = 20.0 / 360.0 * 2.0 * M_PI,
      hpreal rotations = 1.0,
      hpreal baseRadius = 1.0);
      
  ~Worm();
  
  std::vector<hpvec3>* createVerticesAndNormals(hpuint pointsPerTooth = 15, hpuint angleResolution = 50);
  
  hpuint getToothCount();
  hpreal getModule();
  hpreal getPressureAngle();
  hpreal getRotations();
  hpreal getBaseRadius();
  hpreal getReferenceRadius();
  hpreal getMaxRadius();

  void setToothCount(hpuint toothCount);
  void setModule(hpreal module);
  void setPressureAngle(hpreal pressureAngle);
  void setRotations(hpreal rotations);
  void setBaseRadius(hpreal baseRadius);

  TriangleMesh3D_ptr toTriangleMesh(hpuint pointsPerTooth = 15, hpuint angleResolution = 50);
  ZCircleCloud_ptr toZCircleCloud(hpuint pointsPerTooth = 15);

private:
  hpuint m_toothCount;
  hpreal m_module;
  hpreal m_pressureAngle;
  hpreal m_rotations;		//The number of rotations that one tooth does along the Z axis. It can be 0, but then we won't find a suitable involuteGear!
  hpreal m_baseRadius;

  StandardProfile* m_standardProfile;

  void updateValues();
};
typedef std::shared_ptr<Worm> Worm_ptr;

#endif // WORM_H
