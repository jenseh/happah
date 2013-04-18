#ifndef WORM_H
#define WORM_H

#include <glm/glm.hpp>
#include <cmath>

#include <memory>

#include "happah/HappahTypes.h"
#include "happah/geometries/Geometry.h"
#include "happah/geometries/Mesh.h"
#include "happah/geometries/gears/StandardProfile.h"
#include "happah/geometries/ZCircleCloud.h"
#include "happah/LoggingUtils.h"


class Worm : public Geometry {
public:
  Worm(hpuint toothCount = 4,
      hpreal module = 0.13,
      hpreal pressureAngle = 20.0 / 360.0 * 2.0 * M_PI,
      hpuint rotations = 1,
      hpreal faceWidth = 0.2);

  /**
   * @brief Worm constructor setting the height profile and calculating the radius.
   * @param heightProfile
   */
//  Worm(StandardProfile* standardProfile, hpuint toothCount, hpuint rotations, hpreal faceWidth);
      
  ~Worm();
  
  std::vector<hpvec3>* createVerticesAndNormals();
  
  hpreal getToothCount();
  hpreal getModule();
  hpreal getPressureAngle();
  hpreal getRotations();

  hpreal getRadius();

  void setToothCount(hpreal toothCount);
  void setModule(hpreal module);
  void setPressureAngle(hpreal pressureAngle);
  void setRotations(hpreal rotations);

  TriangleMesh_ptr toTriangleMesh();
  ZCircleCloud_ptr toZCircleCloud();

private:
  hpuint m_toothCount;
  hpreal m_module;
  hpreal m_pressureAngle;
  hpuint m_rotations;
  
  hpreal m_radius;
  hpreal m_faceWidth; //TODO: use!

  // TODO: Where should resolution attributes go?
  constexpr static hpuint m_angleResolution = 200;
  constexpr static hpuint m_pointsPerTooth = 200;

  StandardProfile* m_standardProfile;

  void updateValues();
};
typedef std::shared_ptr<Worm> Worm_ptr;

#endif // WORM_H
