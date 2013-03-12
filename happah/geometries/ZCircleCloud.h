#ifndef ZCIRCLECLOUD_H
#define ZCIRCLECLOUD_H

#include <vector>

#include "happah/math/Circle.h"
#include "happah/HappahTypes.h"

class ZCircleCloud
{
public:
  ZCircleCloud(std::vector<hpvec2>* points, std::vector<hpreal>* posZ, int resolutionXY, int resolutionZ, hpvec3& referenceDir);

  int getResolutionXY();
  int getResolutionZ();
  hpmat4x4* getModelMatrix();
  void setModelMatrix(hpmat4x4& modelMatrix);
  hpvec3& getReferenceDir();
  std::vector<hpvec3*>* getClosestPoints(hpvec3 hitPoint);

  hpvec3 getPoint(int posXYIdx, int posZIdx);
//  Circle computeCircle(int posZIdx, int radiusIdx);
  Circle computeOuterCircle(int posZIdx);

private:
  std::vector<hpvec2>* m_points;
  std::vector<hpreal>* m_posZ;

  hpvec3& m_referenceDir;

  int m_resolutionXY;
  int m_resolutionZ;

  hpmat4x4 m_modelMatrix;
};
#endif // ZCIRCLECLOUD_H
