#include <iostream>

#include "happah/simulations/CircularSimulationResult.h"

CircularSimulationResult::CircularSimulationResult(hpuint angleSteps, hpuint posZSteps)
{
  m_angleSteps = angleSteps;
  m_angleRange = 2 * M_PI / m_angleSteps;

  m_posZSteps = posZSteps;
//  hpreal minZ = 0.0f;
//  hpreal maxZ = 1.0f;


  m_entries = new std::unordered_map<hpuint, hpreal>;
  m_referenceDir = hpvec3(1.0, 0.0, 0.0);
}

void CircularSimulationResult::addItem(hpvec3 point, hpuint posZSlot) {
  // Compute the angles of the triangle points to the reference dir
  hpvec3 centerToPoint = glm::normalize(point - hpvec3(0.0, 0.0, point.z));
  hpreal angle = acos(glm::dot(centerToPoint, m_referenceDir));
  hpreal radius = glm::sqrt(point.x * point.x + point.y * point.y);

  hpuint angleSlot = angle / m_angleRange;
  hpuint slot = posZSlot * m_angleSteps + angleSlot;

  hpreal oldRadius = getItem(slot, posZSlot);
  if (oldRadius > radius) {
      m_entries->erase(slot);
      m_entries->insert(std::pair<hpuint, hpreal>(slot, radius));
  }
}

hpreal CircularSimulationResult::getItem(hpuint angleSlot, hpuint posZSlot) {
  int slot = posZSlot * m_angleSteps + angleSlot;

  std::unordered_map<hpuint, hpreal>::const_iterator result = m_entries->find(slot);
  if (result == m_entries->end()) {
    return INFINITY;
  } else {
    return result->second;
  }
}

hpreal CircularSimulationResult::getItem(hpvec3 point, hpuint posZSlot) {
	  // Compute the angles of the triangle points to the reference dir
	  hpvec3 centerToPoint = glm::normalize(point - hpvec3(0.0, 0.0, point.z));
	  hpreal angle = acos(glm::dot(centerToPoint, m_referenceDir));
	  hpreal radius = glm::sqrt(point.x * point.x + point.y * point.y);

	  int angleSlot = angle / m_angleRange;
	  int slot = posZSlot * m_angleSteps + angleSlot;

	  std::unordered_map<hpuint, hpreal>::const_iterator result = m_entries->find(slot);
	  if (result == m_entries->end()) {
	    return INFINITY;
	  } else {
	    return result->second;
	  }
}
