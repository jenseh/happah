#ifndef ZCIRCLECLOUD_H
#define ZCIRCLECLOUD_H

#include <vector>

#include "happah/math/Circle.h"
#include "happah/HappahTypes.h"

class ZCircleCloud
{
public:
  ZCircleCloud(hpreal maxRadius, hpreal startZ, hpreal endZ, hpuint resolutionZ);

  hpuint getResolutionZ();
  hpreal getMaxRadius();

  Circle computeOuterCircle(hpuint posZSlot);

private:
  hpreal m_maxRadius;

  hpreal m_startZ;
  hpreal m_endZ;
  hpuint m_resolutionZ;

  hpreal convertPosZSlotToPosZ(hpuint posZSlot);
};

typedef std::shared_ptr<ZCircleCloud> ZCircleCloud_ptr;

#endif // ZCIRCLECLOUD_H
