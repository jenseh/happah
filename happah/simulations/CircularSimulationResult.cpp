#include "CircularSimulationResult.h"
#include <iostream>


CircularSimulationResult::CircularSimulationResult(int angleSteps, int posZSteps)
{
  m_angleSteps = angleSteps;
  m_angleRange = 2 * M_PI / m_angleSteps;

  m_posZSteps = posZSteps;
//  float minZ = 0.0f;
//  float maxZ = 1.0f;


  m_entries = new hash_map<int, float>;
  m_referenceDir = glm::vec3(1.0f, 0.0f, 0.0f);
}

void CircularSimulationResult::addItem(glm::vec3 point, int posZSlot) {
  // Compute the angles of the triangle points to the reference dir
  glm::vec3 centerToPoint = glm::normalize(point - glm::vec3(0.0f, 0.0f, point.z));
  float angle = acos(glm::dot(centerToPoint, m_referenceDir));
  float radius = glm::sqrt(point.x * point.x + point.y * point.y);

  int angleSlot = angle / m_angleRange;
  int slot = posZSlot * m_angleSteps + angleSlot;

//  std::cout << "addItem: " << slot << std::endl;
//  std::cout << "entries-size: " << m_entries->size()<< std::endl;

  float oldRadius = getItem(slot, posZSlot);
  if (oldRadius > radius) {
      m_entries->erase(slot);
      m_entries->insert(std::pair<int, float>(slot, radius));
  }
}

float CircularSimulationResult::getItem(int angleSlot, int posZSlot) {
  int slot = posZSlot * m_angleSteps + angleSlot;

  hash_map<int, float>::const_iterator result = m_entries->find(slot);
  if (result == m_entries->end()) {
    return INFINITY;
  } else {
    return result->second;
  }
}
