#include "happah/geometries/ZCircleCloud.h"

ZCircleCloud::ZCircleCloud(std::vector<hpvec2>* points, std::vector<hpreal>* posZ, hpuint resolutionXY, hpuint resolutionZ, hpvec3& referenceDir)
  : m_points(points), m_posZ(posZ), m_resolutionXY(resolutionXY), m_resolutionZ(resolutionZ), m_referenceDir(referenceDir) {
  m_modelMatrix = hpmat4x4(); //TODO: check whether this is the identity matrix
}


hpuint ZCircleCloud::getResolutionXY() {
  return m_resolutionXY;
}

hpuint ZCircleCloud::getResolutionZ() {
  return m_resolutionZ;
}

hpmat4x4* ZCircleCloud::getModelMatrix() {
    return &m_modelMatrix;
}

void ZCircleCloud::setModelMatrix(hpmat4x4& modelMatrix) {
    m_modelMatrix = modelMatrix;
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

hpvec3 ZCircleCloud::getPoint(hpuint posXYIdx, hpuint posZIdx) {
  hpvec2 point2D = m_points->at(posXYIdx);
  return hpvec3(point2D.x, point2D.y, m_posZ->at(posZIdx));
}

Circle ZCircleCloud::computeOuterCircle(hpuint posZIdx) {
  hpvec3 center = hpvec3(0.0f, 0.0f, m_posZ->at(posZIdx));
  hpvec3 point = getPoint(m_resolutionXY - 1, posZIdx);

  return Circle(center,
                hpvec3(0.0, 0.0, 1.0),
                2.0);//glm::distance(point, center)
}
