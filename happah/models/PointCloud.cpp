#include "happah/models/PointCloud.h"

PointCloud::PointCloud(std::vector<glm::vec4> *vertexData, std::string name): Drawable(name)
{
  m_vertexData = vertexData;
}
PointCloud::~PointCloud()
{

}

int PointCloud::getTupleSize(){
  return 1;
}

std::vector<glm::vec4>* PointCloud::getVertexData(){
  return m_vertexData;
}
