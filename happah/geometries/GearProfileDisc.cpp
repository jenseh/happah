/*
 * GearProfileDisc.cpp
 *
 *  Created on: 20.03.2013
 *      Author: jlabeit
 */

#include "GearProfileDisc.h"

GearProfileDisc::GearProfileDisc(Gear& gear): Disc(), m_gear(gear) {

}

GearProfileDisc::~GearProfileDisc() {
}

// Create a profile of height values
void GearProfileDisc::createHeightProfile() {

	InvoluteGear* gear = new InvoluteGear();
	std::vector<glm::vec2>* ptr = gear->getToothProfile();;
	m_heightProfile.clear();
	m_radius = 0;
	for( int i = (ptr->size()/2); i >= 0; i--) {
		m_heightProfile.push_back(hpvec2(-ptr->at(i).x, ptr->at(i).y));
		m_radius = glm::max(m_radius,  ptr->at(i).y);
	}
	for( size_t i = 0; i < ptr->size()/2; i++) {
		m_heightProfile.push_back(hpvec2(ptr->at(i)));
	}
	// Invertieren
	for( vector<hpvec2>::iterator it = m_heightProfile.begin(); it != m_heightProfile.end(); ++it) {
		it->y = std::abs(it->y - m_radius);
	}
	delete ptr;
	delete gear;
}

hpreal GearProfileDisc::getRadius() {
	return m_radius;
}

