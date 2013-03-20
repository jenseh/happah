/*
 * GearProfileDisc.cpp
 *
 *  Created on: 20.03.2013
 *      Author: jlabeit
 */

#include "GearProfileDisc.h"

GearProfileDisc::GearProfileDisc(Gear& gear): Disc(), m_gear(gear) {
	m_radius = 0;
}

GearProfileDisc::~GearProfileDisc() {
}

// Create a profile of height values
void GearProfileDisc::createHeightProfile() {

	InvoluteGear* gear = new InvoluteGear();
	std::vector<glm::vec2>* ptr = gear->getToothProfile();;
	m_heightProfile.clear();
	hpreal maxY = 0;
	for( int i = (ptr->size()/2); i >= 0; i--) {
		m_heightProfile.push_back(hpvec2(-ptr->at(i).x, ptr->at(i).y));
		maxY = glm::max(maxY,  ptr->at(i).y);
	}
	for( size_t i = 0; i < ptr->size()/2; i++) {
		m_heightProfile.push_back(hpvec2(ptr->at(i)));
	}
	m_radius = 0;
	// Invertieren
	for( vector<hpvec2>::iterator it = m_heightProfile.begin(); it != m_heightProfile.end(); ++it) {
		it->y = std::abs(it->y - maxY);
		m_radius = glm::max(m_radius, it->y);
	}
	delete ptr;
	delete gear;
}

hpreal GearProfileDisc::getRadius() {
	return m_radius;
}

