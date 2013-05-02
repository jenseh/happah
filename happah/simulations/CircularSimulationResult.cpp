#include <iostream>

#include "happah/simulations/CircularSimulationResult.h"

// This class is always relative to the worm center and in worm coordinates
CircularSimulationResult::CircularSimulationResult(hpuint angleSteps, hpreal startZ, hpreal endZ, hpuint posZSteps) {
	m_angleSteps = angleSteps;
	m_angleRange = 2 * M_PI / m_angleSteps;

	m_startZ = startZ;
	m_endZ = endZ;
	m_posZSteps = posZSteps;

	m_entries = new std::unordered_map<hpuint,hpreal>();
}

CircularSimulationResult::~CircularSimulationResult() {
	delete m_entries;
}

// Adds the item to our hashmap. Returns true if hitpoint was inside the relevant volume or falls otherwise.
bool CircularSimulationResult::addItem(hpvec3 point) {
	// Check whether the point is in our Z range, if not abort
	if (!isInZRange(point)) {
		return false;
	}

	// Compute the angles of the triangle points to the reference dir
	hpreal angle = computeAngle(point);
	hpuint angleSlot = computeAngleSlot(angle);

	hpuint posZSlot = convertPosZToPosZSlot(point.z);
	hpuint slot = computeSlot(angleSlot, posZSlot);

	assert(angleSlot < m_angleSteps);
	assert(posZSlot < m_posZSteps);

	hpreal radius = computeRadiusXY(point);
	hpreal oldRadius = getItem(angleSlot, posZSlot);

	if (oldRadius > radius) {
		m_entries->erase(slot);
		m_entries->insert(std::pair<hpuint,hpreal>(slot, radius));
	}
	return true;
}

hpreal CircularSimulationResult::getItem(hpuint angleSlot, hpuint posZSlot) {
	assert(angleSlot < m_angleSteps);
	assert(posZSlot < m_posZSteps);

	hpuint slot = computeSlot(angleSlot, posZSlot);

	std::unordered_map<hpuint,hpreal>::const_iterator result = m_entries->find(slot);
	if (result == m_entries->end()) {
		return INFINITY;
	} else {
		return result->second;
	}
}

hpreal CircularSimulationResult::computeAngle(hpvec3 point) {
	// Double version: Avoids floating point issues
	double x = point.x;
	double y = point.y;

	double length = sqrt(x * x + y * y);

	x /= length;
	y /= length;

	double aCos = x >= 1.0 ? 0.0 : x <= -1.0 ? M_PI : acos(x);
	double angle = y >= 0.0 ? aCos : 2 * M_PI - aCos;

	return angle;
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
	int result = (posZ - m_startZ) / (m_endZ - m_startZ) * m_posZSteps;

	if (result < 0) {
		return 0;
	} else if (result >= (int) m_posZSteps) {
		return m_posZSteps - 1;
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

	assert(angleSlot < m_angleSteps);
	assert(posZSlot < m_posZSteps);

	std::unordered_map<hpuint,hpreal>::const_iterator result = m_entries->find(slot);
	if (result == m_entries->end()) {
		return INFINITY;
	} else {
		return result->second;
	}
}

hpuint CircularSimulationResult::getPosZSteps() {
	return m_posZSteps;
}

bool CircularSimulationResult::isInZRange(hpvec3 point) {
	hpreal halfIntervalWidth = (m_endZ - m_startZ) / (2.0 * m_posZSteps);
	return m_startZ - halfIntervalWidth <= point.z && point.z <= m_endZ + halfIntervalWidth;
}
