#include <iostream>

#include "happah/simulations/CircularSimulationResult.h"

CircularSimulationResult::CircularSimulationResult(int angleSteps, int posZSteps)
{
  m_angleSteps = angleSteps;
  m_angleRange = 2 * M_PI / m_angleSteps;

  m_posZSteps = posZSteps;
//  hpreal minZ = 0.0f;
//  hpreal maxZ = 1.0f;


  m_entries = new hash_map<int, hpreal>;
  m_referenceDir = hpvec3(1.0f, 0.0f, 0.0f);
}

void CircularSimulationResult::addItem(hpvec3 point, int posZSlot) {
  // Compute the angles of the triangle points to the reference dir
  hpvec3 centerToPoint = glm::normalize(point - hpvec3(0.0f, 0.0f, point.z));
  hpreal angle = acos(glm::dot(centerToPoint, m_referenceDir));
  hpreal radius = glm::sqrt(point.x * point.x + point.y * point.y);

  int angleSlot = angle / m_angleRange;
  int slot = posZSlot * m_angleSteps + angleSlot;

//  std::cout << "addItem: " << slot << std::endl;
//  std::cout << "entries-size: " << m_entries->size()<< std::endl;

  hpreal oldRadius = getItem(slot, posZSlot);
  if (oldRadius > radius) {
      m_entries->erase(slot);
      m_entries->insert(std::pair<int, hpreal>(slot, radius));
  }
}

hpreal CircularSimulationResult::getItem(int angleSlot, int posZSlot) {
  int slot = posZSlot * m_angleSteps + angleSlot;

  hash_map<int, hpreal>::const_iterator result = m_entries->find(slot);
  if (result == m_entries->end()) {
    return INFINITY;
  } else {
    return result->second;
  }
}
