#include "happah/models/ZCircleCloud.h"

ZCircleCloud::ZCircleCloud(std::vector<glm::vec2>* points, std::vector<float>* posZ, int resolutionXY, int resolutionZ, glm::vec3& referenceDir)
  : m_points(points), m_posZ(posZ), m_resolutionXY(resolutionXY), m_resolutionZ(resolutionZ), m_referenceDir(referenceDir) {
  m_modelMatrix.setToIdentity();
}


int ZCircleCloud::getResolutionXY() {
  return m_resolutionXY;
}

int ZCircleCloud::getResolutionZ() {
  return m_resolutionZ;
}

QMatrix4x4* ZCircleCloud::getModelMatrix() {
    return &m_modelMatrix;
}

void ZCircleCloud::setModelMatrix(QMatrix4x4& modelMatrix) {
    m_modelMatrix = modelMatrix;
}

glm::vec3& ZCircleCloud::getReferenceDir() {
  return m_referenceDir;
}

std::vector<glm::vec3*>* ZCircleCloud::getClosestPoints(glm::vec3 hitPoint) {
  std::vector<glm::vec3*>* closestPoints = new std::vector<glm::vec3*>;
  const float maxDist = 0.1f;
  const int maxNum = 2;
//  for (int x = 0; x < m_points->size() && closestPoints->size() < maxNum; x++) {
//      glm::vec3* curPoint = getPoint(x, hitPo;
//      float dist = glm::distance(hitPoint, *curPoint);
//      if (dist < maxDist) {
//          closestPoints->push_back(curPoint);
//      }
//  }
  return closestPoints;
}

//Circle ZCircleCloud::computeCircle(int posZIdx, int radiusIdx) {
//  return Circle(glm::vec3(0.0f, 0.0f,
//                          m_posZ->at(posZIdx)),
//                glm::vec3(0.0f, 0.0f, 1.0f),
//                m_points->at(radiusIdx).radius);
//}

glm::vec3 ZCircleCloud::getPoint(int posXYIdx, int posZIdx) {
  glm::vec2 point2D = m_points->at(posXYIdx);
  return glm::vec3(point2D.x, point2D.y, m_posZ->at(posZIdx));
}

Circle ZCircleCloud::computeOuterCircle(int posZIdx) {
  glm::vec3 center = glm::vec3(0.0f, 0.0f, m_posZ->at(posZIdx));
  glm::vec3 point = getPoint(m_resolutionXY - 1, posZIdx);

  return Circle(center,
                glm::vec3(0.0f, 0.0f, 1.0f),
                2.0f);//glm::distance(point, center)
}
