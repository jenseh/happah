#include "ZCircleCloud.h"

ZCircleCloud::ZCircleCloud(std::vector<float>* radii, std::vector<CirclePoint>* points, std::vector<float>* posZ, int resolutionXY, int resolutionZ, glm::vec3& referenceDir)
  : m_radii(radii), m_points(points), m_posZ(posZ), m_resolutionXY(resolutionXY), m_resolutionZ(resolutionZ), m_referenceDir(referenceDir) {
  modelMatrix_.setToIdentity();
}

//const std::vector<float>* ZCircleCloud::getRadii() {
//  return &m_radii;
//}

int ZCircleCloud::getResolutionXY() {
  return m_resolutionXY;
}

int ZCircleCloud::getResolutionZ() {
  return m_resolutionZ;
}

QMatrix4x4* ZCircleCloud::getModelMatrix() {
    return &modelMatrix_;
}

void ZCircleCloud::setModelMatrix(QMatrix4x4& modelMatrix) {
    modelMatrix_ = modelMatrix;
}

glm::vec3& ZCircleCloud::getReferenceDir() {
  return m_referenceDir;
}

Circle ZCircleCloud::computeCircle(int posZIdx, int radiusIdx) {
  return Circle(glm::vec3(0.0f, 0.0f,
                          m_posZ->at(posZIdx)),
                glm::vec3(0.0f, 0.0f, 1.0f),
                m_radii->at(radiusIdx));
}
