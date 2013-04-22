#include <iostream>

#include "happah/kdtree/BBox.h"


BBox::BBox() {
	m_min = hpvec3(INFINITY, INFINITY, INFINITY);
	m_max = hpvec3(-INFINITY, -INFINITY, -INFINITY);
}
BBox::BBox(hpvec3 min, hpvec3 max)
{
  m_min = min;
  m_max = max;
}

void BBox::addTriangle(Triangle& t){
	for( int i = 0; i < 3; i++){
		for( int j = 0; j < 3; j++){
			m_min[j] = glm::min(m_min[j], t.vertices[i][j]);
			m_max[j] = glm::max(m_max[j], t.vertices[i][j]);
		}
	}
}

hpvec3* BBox::getMin() {
  return &m_min;
}

void BBox::setMin(hpvec3 min) {
  m_min = min;
}

hpvec3* BBox::getMax() {
  return &m_max;
}

void BBox::setMax(hpvec3 max) {
  m_max = max;
}

bool BBox::intersects(BBox& other) {
  return !((m_max.x < other.getMin()->x || m_min.x > other.getMax()->x)
      || (m_max.y < other.getMin()->y || m_min.y > other.getMax()->y)
      || (m_max.z < other.getMin()->z || m_min.z > other.getMax()->z));
}

/*
// Splits the current box into 2 boxes along the specified axis
std::vector<BBox*> BBox::split(int axis, float axisValue) {
  hpvec3 minMiddle, maxMiddle;
  if (axis == 0) {      
      minMiddle[0] = axisValue;
      minMiddle[1] = m_max[1];
      minMiddle[2] = m_max[2];

      maxMiddle[0] = axisValue;
      maxMiddle[1] = m_min[1];
      maxMiddle[2] = m_min[2];
  } else if (axis == 1) {
      minMiddle[0] = m_max[0];
      minMiddle[1] = axisValue;
      minMiddle[2] = m_max[2];

      maxMiddle[0] = m_min[0];
      maxMiddle[1] = axisValue;
      maxMiddle[2] = m_min[2];
  } else {
      minMiddle[0] = m_max[0];
      minMiddle[1] = m_max[1];
      minMiddle[2] = axisValue;

      maxMiddle[0] = m_min[0];
      maxMiddle[1] = m_min[1];
      maxMiddle[2] = axisValue;
  }

  if (axisValue < m_min[axis] || axisValue > m_max[axis]) {
      std::cout << "Error: Axisvalue not inside current box!" << std::endl;
  }

  std::vector<BBox*> boxes;
  boxes.push_back(new BBox(m_min, minMiddle));
  boxes.push_back(new BBox(maxMiddle, m_max));

  return boxes;
}
*/
