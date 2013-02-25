#ifndef POINTCLOUD_H
#define POINTCLOUD_H

#include <vector>
#include <glm/glm.hpp>

#include "Drawable.h"
#include "../../gui/gl/DrawManager.h"
#include "../primitives/Ray.h"
#include "../primitives/Color.h"

class PointCloud :public Drawable
{
public:
  PointCloud(std::vector<glm::vec4> *vertexData, std::string name);
  ~PointCloud();
  std::vector<glm::vec4>* getVertexData();
  int getTupleSize();
 protected:
  std::vector<glm::vec4>*m_vertexData;
};

#endif // POINTCLOUD_H
