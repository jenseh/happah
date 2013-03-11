#ifndef ZCIRCLECLOUD_H
#define ZCIRCLECLOUD_H

#include <QMatrix4x4>
#include <vector>

#include "happah/math/Circle.h"

class ZCircleCloud
{
public:
  ZCircleCloud(std::vector<glm::vec2>* points, std::vector<float>* posZ, int resolutionXY, int resolutionZ, glm::vec3& referenceDir);

  int getResolutionXY();
  int getResolutionZ();
  QMatrix4x4* getModelMatrix();
  void setModelMatrix(QMatrix4x4& modelMatrix);
  glm::vec3& getReferenceDir();
  std::vector<glm::vec3*>* getClosestPoints(glm::vec3 hitPoint);

  glm::vec3 getPoint(int posXYIdx, int posZIdx);
//  Circle computeCircle(int posZIdx, int radiusIdx);
  Circle computeOuterCircle(int posZIdx);

private:
  std::vector<glm::vec2>* m_points;
  std::vector<float>* m_posZ;

  glm::vec3& m_referenceDir;

  int m_resolutionXY;
  int m_resolutionZ;

  QMatrix4x4 m_modelMatrix;
};
#endif // ZCIRCLECLOUD_H
