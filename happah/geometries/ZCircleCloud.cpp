#include "happah/geometries/ZCircleCloud.h"

ZCircleCloud::ZCircleCloud(hpreal maxRadius, hpreal startZ, hpreal endZ, hpuint resolutionZ)
  : m_maxRadius(maxRadius), m_startZ(startZ), m_endZ(endZ), m_resolutionZ(resolutionZ) {
}

hpuint ZCircleCloud::getResolutionZ() {
  return m_resolutionZ;
}

hpreal ZCircleCloud::getMaxRadius() {
	return m_maxRadius;
}

hpreal ZCircleCloud::convertPosZIdxToPosZ(hpuint posZIdx) {
	// Place posZ in the middle of the possible interval to avoid numerical problems
	return m_startZ + (posZIdx + 0.5) * (m_endZ - m_startZ) / m_resolutionZ;
}

Circle ZCircleCloud::computeOuterCircle(hpuint posZIdx) {
  hpreal posZ = convertPosZIdxToPosZ(posZIdx);
  hpvec3 center = hpvec3(0.0, 0.0, posZ);
  hpvec3 normal = hpvec3(0.0, 0.0, 1.0);

  // We add an epsilon to max radius to detect intersections close to the circles
  hpreal epsilon = m_maxRadius / 5.0;
  return Circle(center,
                normal,
                m_maxRadius + epsilon);
}
