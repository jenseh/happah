#ifndef ZCIRCLECLOUD_H
#define ZCIRCLECLOUD_H

#include <vector>

#include <QMatrix4x4>
#include "../primitives/Circle.h"

class ZCircleCloud
{
public:
  ZCircleCloud(std::vector<float>* radii, std::vector<float>* posZ, int resolutionXY, int resolutionZ);

  std::vector<float>* getRadii();
  int getResolutionXY();
  int getResolutionZ();
  QMatrix4x4* getModelMatrix();
  void setModelMatrix(QMatrix4x4& modelMatrix);

  Circle computeCircle(int posZIdx, int radiusIdx);

private:
  std::vector<float>* m_radii;
  std::vector<float>* m_posZ;

  int m_resolutionXY;
  int m_resolutionZ;

  QMatrix4x4 modelMatrix_;
};
#endif // ZCIRCLECLOUD_H
