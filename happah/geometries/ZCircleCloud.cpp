#include "happah/geometries/ZCircleCloud.h"

ZCircleCloud::ZCircleCloud(hpreal maxRadius, hpreal startZ, hpreal endZ, hpuint resolutionZ, hpvec3& referenceDir)
  : m_maxRadius(maxRadius), m_startZ(startZ), m_endZ(endZ), m_resolutionZ(resolutionZ), m_referenceDir(referenceDir) {
}

hpuint ZCircleCloud::getResolutionZ() {
  return m_resolutionZ;
}

hpvec3& ZCircleCloud::getReferenceDir() {
  return m_referenceDir;
}

std::vector<hpvec3*>* ZCircleCloud::getClosestPoints(hpvec3 hitPoint) {
  std::vector<hpvec3*>* closestPoints = new std::vector<hpvec3*>;
  const hpreal maxDist = 0.1;
  const hpuint maxNum = 2;
//  for (hpuint x = 0; x < m_points->size() && closestPoints->size() < maxNum; x++) {
//      hpvec3* curPoint = getPoint(x, hitPo;
//      hpreal dist = hprealdistance(hitPoint, *curPoint);
//      if (dist < maxDist) {
//          closestPoints->push_back(curPoint);
//      }
//  }
  return closestPoints;
}

//Circle ZCircleCloud::computeCircle(hpuint posZIdx, hpuint radiusIdx) {
//  return Circle(hpvec3(0.0f, 0.0f,
//                          m_posZ->at(posZIdx)),
//                hpvec3(0.0f, 0.0f, 1.0f),
//                m_points->at(radiusIdx).radius);
//}

Circle ZCircleCloud::computeOuterCircle(hpuint posZIdx) {
  hpreal posZ = m_startZ + posZIdx * (m_endZ - m_startZ) / m_resolutionZ;
  hpvec3 center = hpvec3(0.0, 0.0, posZ);
  hpvec3 normal = hpvec3(0.0, 0.0, 1.0);

  return Circle(center,
                normal,
                m_maxRadius);
}
