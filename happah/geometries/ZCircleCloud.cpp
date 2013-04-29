#include "happah/geometries/ZCircleCloud.h"

ZCircleCloud::ZCircleCloud(hpreal maxRadius, hpreal startZ, hpreal endZ, hpuint resolutionZ)
  : m_maxRadius(maxRadius), m_startZ(startZ), m_endZ(endZ), m_resolutionZ(resolutionZ) {
}

Circle ZCircleCloud::computeOuterCircle(hpuint posZSlot) {
  // Convert the specified z slot to a z value in local coordinates
  hpreal posZ = convertPosZSlotToPosZ(posZSlot);

  // Specify the center and normal of our circle
  hpvec3 center = hpvec3(0.0, 0.0, posZ);
  hpvec3 normal = hpvec3(0.0, 0.0, 1.0);

  // Add an epsilon to max radius to detect intersections close to the circles
  hpreal epsilon = m_maxRadius / 100.0;
  return Circle(center,
                normal,
                m_maxRadius + epsilon);
}

hpreal ZCircleCloud::convertPosZSlotToPosZ(hpuint posZSlot) {
	// Place posZ in the middle of the possible interval to avoid numerical
	// problems at the borders.
	return m_startZ + (posZSlot + 0.5) * (m_endZ - m_startZ) / m_resolutionZ;
}

hpreal ZCircleCloud::getMaxRadius() {
	return m_maxRadius;
}

hpuint ZCircleCloud::getPosZSteps() {
  return m_resolutionZ;
}
