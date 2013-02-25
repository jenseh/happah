#ifndef POINTCLOUD_H
#define POINTCLOUD_H

#include <glm/glm.hpp>
#include <string>
#include <vector>

#include "happah/models/Drawable.h"
#include "happah/primitives/Color.h"
#include "happah/primitives/Ray.h"

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
