#include "happah/geometries/gears/BasicRack.h"

// Constructor for a general gear. Gears are always centered on 0,0,0 with the z axis being the gear axis.
BasicRack::BasicRack(hpreal length, hpreal depth, hpreal height, int toothCount, std::string name) : NonDrawable(name) {
    m_length = length;
    m_depth = depth;
    m_height = height;
    m_toothCount = toothCount;
    // Modul = Teilung / PI
    m_module = (length / (hpreal)toothCount) / M_PI;
}

BasicRack::~BasicRack() {
}

// Create a profile of height values for one partition (german: Teilung)
// x-values must be between 0 and p (partition, german: Teilung)
// y-values must be between -p and p (height)
void BasicRack::createHeightProfilePartition() {
    m_heightProfilePartition = std::vector<glm::vec2>();

    m_standardProfile = new StandardProfile(m_module, 10 / 180.0 * M_PI, 0, 0);
    m_standardProfile->getProfilePartition(m_heightProfilePartition,
            SEGMENT_COUNT);
    //createApproximatedPartition();
}

// Create a profile of height values
// x-values must be between 0 and 1 (position)
// y-values must be between -1 and 1 (height)
void BasicRack::createHeightProfile() {
    createHeightProfilePartition();
    m_heightProfile = std::vector<glm::vec2>();

    for (int i = 0; i < m_toothCount; i++) {
        for (unsigned int j = 0; j < m_heightProfilePartition.size(); j++) {
            hpreal position = m_heightProfilePartition[j].x + i * m_module * M_PI;
            hpreal height = m_heightProfilePartition[j].y;
            m_heightProfile.push_back(glm::vec2(position, height));
            //cout << position << ": " << height << std::endl;
        }
    }
    // Go down and back to the start
    glm::vec2 tempVec = m_heightProfile[m_heightProfile.size() - 1];
    tempVec.y -= m_height; // Mach unten
    m_heightProfile.push_back(tempVec);
    tempVec = m_heightProfile[0]; // nach links
    tempVec.y -= m_height; // und unten
    m_heightProfile.push_back(tempVec);
    tempVec.y += m_height; // und wieder hoch
    m_heightProfile.push_back(tempVec);

    //m_heightProfile.push_back(m_heightProfile[0]);
}

// This creates the quads for a gear. The gear axis is the model's z-axis.
QuadMesh* BasicRack::toQuadMesh() {
    hpreal dz = m_depth / Z_DETAIL_LEVEL;

    // Create the height profile given the current gear settings
    createHeightProfile();
    for (int i = 0; i < Z_DETAIL_LEVEL; i++) {
        hpreal z = i * dz;
        glm::vec4 a, b, c, d, norm;
        a.z = z;
        a.w = 1.0f;

        b.z = z;
        b.w = 1.0f;

        c.z = z + dz;
        c.w = 1.0f;

        d.z = z + dz;
        d.w = 1.0f;
        for (unsigned int segmentNum = 0; segmentNum < m_heightProfile.size()-1;
                segmentNum++) {

            a.x = m_heightProfile[segmentNum + 1].x;
            a.y = m_heightProfile[segmentNum + 1].y;

            b.x = m_heightProfile[segmentNum].x;
            b.y = m_heightProfile[segmentNum].y;

            c.x = m_heightProfile[segmentNum].x;
            c.y = m_heightProfile[segmentNum].y;

            d.x = m_heightProfile[segmentNum + 1].x;
            d.y = m_heightProfile[segmentNum + 1].y;

            norm = glm::vec4(
                    glm::normalize(
                            glm::cross(glm::vec3(0.0f, 0.0f, c.z - b.z),
                                    glm::vec3(a.x - b.x, a.y - b.y, 0.0f))),
                    1.0f);

            m_vertexData.push_back(a);
            //m_vertexData.push_back(normNext);
            m_vertexData.push_back(norm);
            m_vertexData.push_back(b);
            m_vertexData.push_back(norm);
            m_vertexData.push_back(c);
            m_vertexData.push_back(norm);
            m_vertexData.push_back(d);
            //m_vertexData.push_back(normNext);
            m_vertexData.push_back(norm);
        }
    }

    QuadMesh* result = new QuadMesh(m_vertexData, concatStringNumber(m_name + " - Instance ", m_objectIdCounter++));
    result->setModelMatrix(m_modelMatrix);
    return result;
}

TriangleMesh* BasicRack::toTriangleMesh() {
  //TODO: Implement this function
  return 0;
}
