/*
 * BasicRack.h
 *
 *  Created on: Dez 5, 2012
 *      Author: julian
 */

#include "Disc.h"


// Constructor for a general gear. Gears are always centered on 0,0,0 with the z axis being the gear axis.
Disc::Disc(hpreal radius, std::string name) : NonDrawable(name) {
    m_radius = radius; // doppelt so groß wie ein zahn
    m_module = m_radius/2.0;
    m_length = m_module * M_PI;
    m_standardProfile = new StandardProfile(m_module, 30 / 180.0 * M_PI, 0, 0);
}

Disc::~Disc() {
    delete m_standardProfile;
}

hpreal Disc::getRadius() {
    return m_radius;
}

// Create a profile of height values
void Disc::createHeightProfile() {
    m_heightProfile = std::vector<glm::vec2>();
    m_heightProfile.resize(SEGMENT_COUNT);
    hpreal x = m_length / 2.0;
    hpreal deltaX = m_length/(double)SEGMENT_COUNT;
    for( int i = 0; i < SEGMENT_COUNT; i++){
        m_heightProfile[i].x = x;
        m_heightProfile[i].y = m_standardProfile->getHeight(x) + m_module;
        x += deltaX;
    }
}

// This creates the quads for a gear. The gear axis is the model's z-axis.
void Disc::createVertexData() {
    m_vertexData.clear();
    float dalpha = 2*M_PI/ Z_DETAIL_LEVEL;

    // Create the height profile given the current gear settings
    createHeightProfile();


    // draw the sides (german: Mantelflaechen) of the gear
    // this is the important part where the height profile will come into play
    for (int i = 0; i < Z_DETAIL_LEVEL; i++) {
        hpreal alpha1 = i * dalpha;
        hpreal sinAlpha1 = sin(alpha1);
        hpreal cosAlpha1 = cos(alpha1);
        hpreal alpha2 = alpha1 + dalpha;
        hpreal sinAlpha2 = sin(alpha2);
        hpreal cosAlpha2 = cos(alpha2);
        for (unsigned int segmentNum = 0; segmentNum < m_heightProfile.size()-1;
                segmentNum++) {

            glm::vec4 a, b, c, d, normNext, norm;

            a.x = m_heightProfile[segmentNum+1].x;
            a.y = sinAlpha1 * m_heightProfile[segmentNum+1].y;
            a.z = cosAlpha1 * m_heightProfile[segmentNum+1].y;
            a.w = 1.0f;

            b.x = m_heightProfile[segmentNum].x;
            b.y = sinAlpha1 * m_heightProfile[segmentNum].y;
            b.z = cosAlpha1 * m_heightProfile[segmentNum].y;
            b.w = 1.0f;

            c.x = m_heightProfile[segmentNum].x;
            c.y = sinAlpha2 * m_heightProfile[segmentNum].y;
            c.z = cosAlpha2 * m_heightProfile[segmentNum].y;
            c.w = 1.0f;

            d.x = m_heightProfile[segmentNum+1].x;
            d.y = sinAlpha2 * m_heightProfile[segmentNum+1].y;
            d.z = cosAlpha2 * m_heightProfile[segmentNum+1].y;
            d.w = 1.0f;

            /*norm = glm::vec4(
                    glm::normalize(
                            glm::cross(glm::vec3(0.0f, 0.0f, c.z - b.z),
                                    glm::vec3(a.x - b.x, a.y - b.y, 0.0f))),
                    1.0f);*/
            glm::vec3 tempNorm = glm::cross( (glm::vec3)(a - b), (glm::vec3)(c - b));
            norm.x = tempNorm.x;
            norm.y = tempNorm.y;
            norm.z = tempNorm.z;
            norm.w = 1.0f;
            norm = glm::normalize(norm);




            m_vertexData.push_back(a);
            //dataPushback(normNext);
            m_vertexData.push_back(norm);
            m_vertexData.push_back(b);
            m_vertexData.push_back(norm);
            m_vertexData.push_back(c);
            m_vertexData.push_back(norm);
            m_vertexData.push_back(d);
            //dataPushback(normNext);
            m_vertexData.push_back(norm);
        }
    }
}

QuadMesh* Disc::toQuadMesh(){
    createVertexData();
    QuadMesh* result = new QuadMesh(m_vertexData, m_name + " - Instance 1");
    result->setModelMatrix(m_modelMatrix);
    return result;
}

