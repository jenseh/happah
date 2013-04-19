#ifndef ZCIRCLECLOUD_H
#define ZCIRCLECLOUD_H

#include <vector>

#include "happah/math/Circle.h"
#include "happah/HappahTypes.h"

class ZCircleCloud
{
public:
  ZCircleCloud(hpreal maxRadius, hpreal startZ, hpreal endZ, hpuint resolutionZ, hpvec3& referenceDir);

  hpuint getResolutionZ();
  hpvec3 getReferenceDir();
  hpreal getMaxRadius();

  hpuint convertPosZToPosZIdx(hpreal posZ);
  Circle computeOuterCircle(hpuint posZIdx);

private:
  hpreal m_maxRadius;
  hpreal m_startZ;
  hpreal m_endZ;

  hpuint m_resolutionZ;

  hpvec3& m_referenceDir;
};

typedef std::shared_ptr<ZCircleCloud> ZCircleCloud_ptr;

#endif // ZCIRCLECLOUD_H
