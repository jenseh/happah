#include <iostream>

#include "happah/simulations/CircularSimulationResult.h"

// This class is always relative to the worm center and in worm coordinates
CircularSimulationResult::CircularSimulationResult(hpuint angleSteps, hpreal startZ, hpreal endZ, hpuint resolutionZ)
{
  m_angleSteps = angleSteps;
  m_angleRange = 2 * M_PI / m_angleSteps;

  m_startZ = startZ;
  m_endZ = endZ;
  m_resolutionZ = resolutionZ;


  m_entries = new std::unordered_map<hpuint, hpreal>;
  m_referenceDir = hpvec2(1.0, 0.0);
}

CircularSimulationResult::~CircularSimulationResult() {
	delete m_entries;
}

void CircularSimulationResult::addItem(hpvec3 point) {
	// Check whether the point is in our Z range, if not abort
	if (!isInZRange(point)) {
//		std::cout << "Rejecting point: " << point.x << " " << point.y << " " << point.z << std::endl;
		return;
	}

  // Compute the angles of the triangle points to the reference dir
  hpreal angle = computeAngle(point);
  hpuint angleSlot = round(angle / m_angleRange);

  hpuint posZSlot = convertPosZToPosZIdx(point.z);
  hpuint slot = posZSlot * m_angleSteps + angleSlot;

	std::cout << "Adding point: " << point.x << " " << point.y << " " << point.z << "->" << posZSlot << std::endl;

  assert(angleSlot < m_angleSteps);
  assert(posZSlot < m_resolutionZ);

  hpreal radius = computeRadiusXY(point);
//  std::cout << "angle: " << angle << ", radius: " << radius << std::endl;
  hpreal oldRadius = getItem(angleSlot, posZSlot);

  if (oldRadius > radius) {
      m_entries->erase(slot);
      m_entries->insert(std::pair<hpuint, hpreal>(slot, radius));
  }
}

hpreal CircularSimulationResult::getItem(hpuint angleSlot, hpuint posZSlot) {
	assert(angleSlot < m_angleSteps);
	assert(posZSlot < m_resolutionZ);

  int slot = posZSlot * m_angleSteps + angleSlot;

  std::unordered_map<hpuint, hpreal>::const_iterator result = m_entries->find(slot);
  if (result == m_entries->end()) {
    return INFINITY;
  } else {
    return result->second;
  }
}

// This function computes a radius in the XY plane (ignoring Z)
hpreal CircularSimulationResult::computeRadiusXY(hpvec3 point) {
	return glm::sqrt(point.x * point.x + point.y * point.y);
}

hpreal CircularSimulationResult::computeAngle(hpvec3 point) {
	  hpvec2 centerToPoint = glm::normalize(hpvec2(point.x, point.y));
	  hpreal angle = acos(glm::dot(centerToPoint, m_referenceDir));
	  if (centerToPoint.y < 0) angle = M_PI - angle;
	  return angle;
}

hpuint CircularSimulationResult::convertPosZToPosZIdx(hpreal posZ) {
	return (hpuint) round((posZ - m_startZ) / (m_endZ - m_startZ));
}

hpreal CircularSimulationResult::getItem(hpvec3 point) {
	// Check whether the point is in our Z range, if not abort and return positive infinity
	if (!isInZRange(point)) {
		return INFINITY;
	}

	  // Compute the angles of the triangle points to the reference dir
	  hpreal angle = computeAngle(point);
	  hpuint angleSlot = round(angle / m_angleRange);

	  hpuint posZSlot = convertPosZToPosZIdx(point.z);
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

bool CircularSimulationResult::isInZRange(hpvec3 point) {
	hpreal epsilon = 10e-7;
	return m_startZ - epsilon <= point.z && point.z <= m_endZ + epsilon;
}
