#include "happah/geometries/ZCircleCloud.h"

ZCircleCloud::ZCircleCloud(hpreal maxRadius, hpreal startZ, hpreal endZ, hpuint resolutionZ, hpvec3 referenceDir)
  : m_maxRadius(maxRadius), m_startZ(startZ), m_endZ(endZ), m_resolutionZ(resolutionZ), m_referenceDir(referenceDir) {
}

hpuint ZCircleCloud::getResolutionZ() {
  return m_resolutionZ;
}

hpvec3 ZCircleCloud::getReferenceDir() {
  return m_referenceDir;
}

hpreal ZCircleCloud::getMaxRadius() {
	return m_maxRadius;
}

hpuint ZCircleCloud::convertPosZToPosZIdx(hpreal posZ) {
	return (hpuint) round((posZ - m_startZ) / (m_endZ - m_startZ));
}

hpreal ZCircleCloud::convertPosZIdxToPosZ(hpuint posZIdx) {
	return m_startZ + posZIdx * (m_endZ - m_startZ) / m_resolutionZ;
}

Circle ZCircleCloud::computeOuterCircle(hpuint posZIdx) {
  hpreal posZ = convertPosZIdxToPosZ(posZIdx);
  hpvec3 center = hpvec3(0.0, 0.0, posZ);
  hpvec3 normal = hpvec3(0.0, 0.0, 1.0);

  // We add an epsilon to max radius to detect intersections close to the worm
//  std::cout << "m_maxRadius" << m_maxRadius << std::endl;
  hpreal epsilon = m_maxRadius / 5.0;
  return Circle(center,
                normal,
                m_maxRadius + epsilon);
}
