#include <iostream>

#include "happah/simulations/CircularSimulationResult.h"

// This class is always relative to the worm center and in worm coordinates
CircularSimulationResult::CircularSimulationResult(hpuint angleSteps, hpreal startZ, hpreal endZ, hpuint resolutionZ) {
	m_angleSteps = angleSteps;
	m_angleRange = 2 * M_PI / m_angleSteps;

	m_startZ = startZ;
	m_endZ = endZ;
	m_resolutionZ = resolutionZ;

	m_entries = new std::unordered_map<hpuint,hpreal>();
}

CircularSimulationResult::~CircularSimulationResult() {
	delete m_entries;
}

// Adds the item to our hashmap. Returns true if hitpoint was inside the relevant volume or falls otherwise.
bool CircularSimulationResult::addItem(hpvec3 point) {
	// Check whether the point is in our Z range, if not abort
	if (!isInZRange(point)) {
		std::cout << "Rejecting point: " << point.x << " " << point.y << " " << point.z << std::endl;
		return false;
	}

	// Compute the angles of the triangle points to the reference dir
	hpreal angle = computeAngle(point);
	hpuint angleSlot = computeAngleSlot(angle);

	hpuint posZSlot = convertPosZToPosZSlot(point.z);
	hpuint slot = computeSlot(angleSlot, posZSlot);

//	std::cout << "Adding point: " << point.x << " " << point.y << " " << point.z << " -> " << angleSlot << " : " << posZSlot << std::endl;

	assert(angleSlot < m_angleSteps);
	assert(posZSlot < m_resolutionZ);

	hpreal radius = computeRadiusXY(point);
//  std::cout << "angle: " << angle << ", radius: " << radius << std::endl;
	hpreal oldRadius = getItem(angleSlot, posZSlot);

	if (oldRadius > radius) {
		m_entries->erase(slot);
		m_entries->insert(std::pair<hpuint,hpreal>(slot, radius));
	}
	return true;
}

hpreal CircularSimulationResult::getItem(hpuint angleSlot, hpuint posZSlot) {
	assert(angleSlot < m_angleSteps);
	assert(posZSlot < m_resolutionZ);

	hpuint slot = computeSlot(angleSlot, posZSlot);

	std::unordered_map<hpuint,hpreal>::const_iterator result = m_entries->find(slot);
	if (result == m_entries->end()) {
		return INFINITY;
	} else {
		return result->second;
	}
}

hpreal CircularSimulationResult::computeAngle(hpvec3 point) {
	// Double version: Works well
	double x = point.x;
	double y = point.y;

	double length = sqrt(x * x + y * y);

	x /= length;
	y /= length;

	double aCos = x >= 1.0 ? 0.0 : x <= -1.0 ? M_PI : acos(x);
	double angle = y >= 0.0 ? aCos : 2 * M_PI - aCos;

	return angle;

	// Float version: Results in nasty bugs
//	hpreal normalizedX = point.x / sqrt(point.x * point.x);
//	hpreal aCos = normalizedX >= 0.99 ? 0.0 : normalizedX < -0.99 ? M_PI : acos(normalizedX);
//	hpreal angle = point.y >= 0.0 ? aCos : 2 * M_PI - aCos;
//	return angle;
}

hpuint CircularSimulationResult::computeAngleSlot(hpreal angle) {
	hpreal result = angle / m_angleRange;

	if (result < 0){
		return m_angleSteps - 1 + result;
	} else if (result >= m_angleSteps) {
		return result - m_angleSteps;
	} else if (result == m_angleSteps) {
		return m_angleSteps - 1;
	} else {
		return (hpuint) result;
	}
}

hpuint CircularSimulationResult::computeSlot(hpuint angleSlot, hpuint posZSlot) {
	hpuint slot = posZSlot * m_angleSteps + angleSlot;
	return slot;
}

hpuint CircularSimulationResult::convertPosZToPosZSlot(hpreal posZ) {
	int result = (posZ - m_startZ) / (m_endZ - m_startZ) * m_resolutionZ;

	if (result < 0) {
		return 0;
	} else if (result >= (int) m_resolutionZ) {
		return m_resolutionZ - 1;
	} else {
		return (hpuint) result;
	}
}

// This function computes a radius in the XY plane (ignoring Z)
hpreal CircularSimulationResult::computeRadiusXY(hpvec3 point) {
	return glm::sqrt(point.x * point.x + point.y * point.y);
}

hpreal CircularSimulationResult::getItem(hpvec3 point) {
	// Check whether the point is in our Z range, if not abort and return positive infinity
	if (!isInZRange(point)) {
		return INFINITY;
	}

	// Compute the angles of the triangle points to the reference dir
	hpreal angle = computeAngle(point);
	hpuint angleSlot = computeAngleSlot(angle);

	hpuint posZSlot = convertPosZToPosZSlot(point.z);
	hpuint slot = computeSlot(angleSlot, posZSlot);

//	std::cout << "Getting point: " << angle << " -> " << angleSlot << std::endl;

	assert(angleSlot < m_angleSteps);
	assert(posZSlot < m_resolutionZ);

	std::unordered_map<hpuint,hpreal>::const_iterator result = m_entries->find(slot);
	if (result == m_entries->end()) {
		return INFINITY;
	} else {
		return result->second;
	}
}

hpuint CircularSimulationResult::getResolutionZ() {
	return m_resolutionZ;
}

bool CircularSimulationResult::isInZRange(hpvec3 point) {
	hpreal halfIntervalWidth = (m_endZ - m_startZ) / (2.0 * m_resolutionZ);
	return m_startZ - halfIntervalWidth <= point.z && point.z <= m_endZ + halfIntervalWidth;
}
