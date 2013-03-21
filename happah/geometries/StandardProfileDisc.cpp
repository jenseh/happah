#include "StandardProfileDisc.h"

StandardProfileDisc::StandardProfileDisc(hpreal radius): Disc(), m_radius(radius) {
    m_standardProfile = NULL;
    updateValues();
}

StandardProfileDisc::~StandardProfileDisc() {
	delete m_standardProfile;
}

void StandardProfileDisc::createHeightProfile() {
	m_heightProfile = std::vector<glm::vec2>();
    m_heightProfile.resize(HEIGHT_PROFILE_DETAIL_LEVEL);
    hpreal x = m_length / 2.0;
    hpreal deltaX = m_length/(double)HEIGHT_PROFILE_DETAIL_LEVEL;
    for( int i = 0; i < HEIGHT_PROFILE_DETAIL_LEVEL; i++){
        m_heightProfile[i].x = x - m_length;
        m_heightProfile[i].y = m_standardProfile->getHeight(x) + m_module;
        x += deltaX;
    }
}
hpreal StandardProfileDisc::getRadius() {
	return m_radius;
}

void StandardProfileDisc::setRadius(hpreal radius) {
	m_radius = radius;
	updateValues();
}

void StandardProfileDisc::updateValues(){
    m_module = m_radius / 2.0;
    m_length = m_module * M_PI;
    if( m_standardProfile != NULL )
    	delete m_standardProfile;
    m_standardProfile = new StandardProfile(m_module, 30 / 180.0 * M_PI, 0, 0);
}

