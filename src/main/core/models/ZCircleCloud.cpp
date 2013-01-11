#include "ZCircleCloud.h"

ZCircleCloud::ZCircleCloud(std::vector<float>* radii, std::vector<float>* posZ, int resolutionXY, int resolutionZ)
  : m_resolutionXY(resolutionXY), m_resolutionZ(resolutionZ) {
  m_radii = radii;
  m_posZ = posZ;
  modelMatrix_.setToIdentity();
}

std::vector<float>* ZCircleCloud::getRadii() {
  return m_radii;
}

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

Circle ZCircleCloud::computeCircle(int posZIdx, int radiusIdx) {
  return Circle(glm::vec3(0.0f, 0.0f, m_posZ->at(posZIdx)), glm::vec3(0.0f, 0.0f, 1.0f), m_radii->at(radiusIdx));
}
