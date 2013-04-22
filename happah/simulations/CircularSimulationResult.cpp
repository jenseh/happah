#include <iostream>

#include "happah/simulations/CircularSimulationResult.h"

// This class is always relative to the worm center and in worm coordinates
CircularSimulationResult::CircularSimulationResult(hpuint angleSteps, hpuint resolutionZ)
{
  m_angleSteps = angleSteps;
  m_angleRange = 2 * M_PI / m_angleSteps;

  m_resolutionZ = resolutionZ;


  m_entries = new std::unordered_map<hpuint, hpreal>;
  m_referenceDir = hpvec2(1.0, 0.0);
}

CircularSimulationResult::~CircularSimulationResult() {
	delete m_entries;
}

void CircularSimulationResult::addItem(hpvec3 point, hpuint posZSlot) {
  // Compute the angles of the triangle points to the reference dir
  hpreal angle = computeAngle(point);
  hpreal radius = glm::length(point);

//  std::cout << "angle: " << angle << ", radius: " << radius << std::endl;

  hpuint angleSlot = round(angle / m_angleRange);
  hpuint slot = posZSlot * m_angleSteps + angleSlot;

  assert(angleSlot < m_angleSteps);
  assert(posZSlot < m_resolutionZ);

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

hpreal CircularSimulationResult::computeAngle(hpvec3 point) {
	  hpvec2 centerToPoint = glm::normalize(hpvec2(point.x, point.y));
	  hpreal angle = acos(glm::dot(centerToPoint, m_referenceDir));
	  if (centerToPoint.y < 0) angle = M_PI - angle;
	  return angle;
}

hpreal CircularSimulationResult::getItem(hpvec3 point, hpuint posZSlot) {
	  // Compute the angles of the triangle points to the reference dir
	  hpreal angle = computeAngle(point);
	  hpuint angleSlot = round(angle / m_angleRange);
	  hpuint slot = posZSlot * m_angleSteps + angleSlot;

	  assert(angleSlot < m_angleSteps);
	  assert(posZSlot < m_resolutionZ);

	  std::unordered_map<hpuint, hpreal>::const_iterator result = m_entries->find(slot);
	  if (result == m_entries->end()) {
	    return INFINITY;
	  } else {
	    return result->second;
	  }
}
