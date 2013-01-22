#ifndef ZCIRCLECLOUD_H
#define ZCIRCLECLOUD_H

#include <vector>

#include <QMatrix4x4>
#include "../primitives/Circle.h"

class ZCircleCloud
{
public:
  ZCircleCloud(std::vector<float>* radii, std::vector<CirclePoint>* points, std::vector<float>* posZ, int resolutionXY, int resolutionZ, glm::vec3& referenceDir);

//  std::vector<float>* getRadii();
  int getResolutionXY();
  int getResolutionZ();
  QMatrix4x4* getModelMatrix();
  void setModelMatrix(QMatrix4x4& modelMatrix);
  glm::vec3& getReferenceDir();

  Circle computeCircle(int posZIdx, int radiusIdx);

private:
  std::vector<float>* m_radii;
  std::vector<CirclePoint>* m_points;
  std::vector<float>* m_posZ;

  glm::vec3& m_referenceDir;

  int m_resolutionXY;
  int m_resolutionZ;

  QMatrix4x4 modelMatrix_;
};
#endif // ZCIRCLECLOUD_H
