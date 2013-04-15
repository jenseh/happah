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
    heightProfilePartition = std::vector<glm::vec2>();

    m_standardProfile = new StandardProfile(m_module, 10 / 180.0 * M_PI, 0, 0);
    m_standardProfile->getProfilePartition(heightProfilePartition,
            SEGMENT_COUNT);
    //createApproximatedPartition();
}

// Create a profile of height values
// x-values must be between 0 and 1 (position)
// y-values must be between -1 and 1 (height)
void BasicRack::createHeightProfile() {
    createHeightProfilePartition();
    heightProfile = std::vector<glm::vec2>();

    for (int i = 0; i < m_toothCount; i++) {
        for (unsigned int j = 0; j < heightProfilePartition.size(); j++) {
            hpreal position = heightProfilePartition[j].x + i * m_module * M_PI;
            hpreal height = heightProfilePartition[j].y;
            heightProfile.push_back(glm::vec2(position, height));
            //cout << position << ": " << height << std::endl;
        }
    }
    // Go down and back to the start
    glm::vec2 tempVec = heightProfile[heightProfile.size() - 1];
    tempVec.y -= m_height; // Mach unten
    heightProfile.push_back(tempVec);
    tempVec = heightProfile[0]; // nach links
    tempVec.y -= m_height; // und unten
    heightProfile.push_back(tempVec);
    tempVec.y += m_height; // und wieder hoch
    heightProfile.push_back(tempVec);

    //heightProfile.push_back(heightProfile[0]);
}

std::vector<hpvec3>* BasicRack::createVerticesAndNormals() {
	//TODO: implement this
	return 0;
}

// This creates the quads for a gear. The gear axis is the model's z-axis.
//QuadMesh* BasicRack::toQuadMesh() {
//    std::vector<hpvec3>* verticesAndNormals = createVerticesAndNormals();
//    std::vector<hpuint>* indices = new std::vector<hpuint>();
//    hpreal dz = m_depth / Z_DETAIL_LEVEL;
//
//    // Create the height profile given the current gear settings
//    std::vector<hpvec2> heightProfile = createHeightProfile();
//    for (int i = 0; i < Z_DETAIL_LEVEL; i++) {
//        hpreal z = i * dz;
//        glm::vec4 a, b, c, d, norm;
//        a.z = z;
//        a.w = 1.0f;
//
//        b.z = z;
//        b.w = 1.0f;
//
//        c.z = z + dz;
//        c.w = 1.0f;
//
//        d.z = z + dz;
//        d.w = 1.0f;
//        for (unsigned int segmentNum = 0; segmentNum < heightProfile.size()-1;
//                segmentNum++) {
//
//            a.x = heightProfile[segmentNum + 1].x;
//            a.y = heightProfile[segmentNum + 1].y;
//
//            b.x = heightProfile[segmentNum].x;
//            b.y = heightProfile[segmentNum].y;
//
//            c.x = heightProfile[segmentNum].x;
//            c.y = heightProfile[segmentNum].y;
//
//            d.x = heightProfile[segmentNum + 1].x;
//            d.y = heightProfile[segmentNum + 1].y;
//
//            norm = glm::vec4(
//                    glm::normalize(
//                            glm::cross(glm::vec3(0.0f, 0.0f, c.z - b.z),
//                                    glm::vec3(a.x - b.x, a.y - b.y, 0.0f))),
//                    1.0f);
//
//            verticesAndNormals.push_back(a);
//            //verticesAndNormals.push_back(normNext);
//            verticesAndNormals.push_back(norm);
//            verticesAndNormals.push_back(b);
//            verticesAndNormals.push_back(norm);
//            verticesAndNormals.push_back(c);
//            verticesAndNormals.push_back(norm);
//            verticesAndNormals.push_back(d);
//            //verticesAndNormals.push_back(normNext);
//            verticesAndNormals.push_back(norm);
//        }
//    }
//
//    QuadMesh* result = new QuadMesh(verticesAndNormals, indices);
//    return result;
//}

TriangleMesh* BasicRack::toTriangleMesh() {
    std::vector<hpvec3>* verticesAndNormals = createVerticesAndNormals();
    std::vector<hpuint>* indices = new std::vector<hpuint>();
    hpuint indexCount =  verticesAndNormals->size() / 2;
    indices->reserve(indexCount);
    for (hpuint index = 0; index < indexCount; index++) {
    	indices->push_back(index);
    }
    TriangleMesh* result = new TriangleMesh(verticesAndNormals, indices);
    return result;
}
