#include "BasicRack.h"

// Constructor for a general gear. Gears are always centered on 0,0,0 with the z axis being the gear axis.
BasicRack::BasicRack(float length, float depth, float height, int toothCount) {
    length_ = length;
    depth_ = depth;
    height_ = height;
    toothCount_ = toothCount;
    // Modul = Teilung / PI
    module_ = (length / (float)toothCount) / M_PI;
}

BasicRack::~BasicRack() {
}

// Create a profile of height values for one partition (german: Teilung)
// x-values must be between 0 and p (partition, german: Teilung)
// y-values must be between -p and p (height)
void BasicRack::createHeightProfilePartition() {
    heightProfilePartition_ = std::vector<glm::vec2>();

    standardProfile = new StandardProfile(module_, 10 / 180.0 * M_PI, 0, 0);
    standardProfile->getProfilePartition(heightProfilePartition_,
            SEGMENT_COUNT);
    //createApproximatedPartition();
}

// Create a profile of height values
// x-values must be between 0 and 1 (position)
// y-values must be between -1 and 1 (height)
void BasicRack::createHeightProfile() {
    createHeightProfilePartition();
    heightProfile_ = std::vector<glm::vec2>();

    for (int i = 0; i < toothCount_; i++) {
        for (unsigned int j = 0; j < heightProfilePartition_.size(); j++) {
            float position = heightProfilePartition_[j].x + i * module_ * M_PI;
            float height = heightProfilePartition_[j].y;
            heightProfile_.push_back(glm::vec2(position, height));
            //cout << position << ": " << height << std::endl;
        }
    }
    // Go down and back to the start
    glm::vec2 tempVec = heightProfile_[heightProfile_.size() - 1];
    tempVec.y -= height_; // Mach unten
    heightProfile_.push_back(tempVec);
    tempVec = heightProfile_[0]; // nach links
    tempVec.y -= height_; // und unten
    heightProfile_.push_back(tempVec);
    tempVec.y += height_; // und wieder hoch
    heightProfile_.push_back(tempVec);

    //heightProfile_.push_back(heightProfile_[0]);
}

// This creates the quads for a gear. The gear axis is the model's z-axis.
QuadMesh* BasicRack::toQuadMesh() {
    float dz = depth_ / Z_DETAIL_LEVEL;

    // Create the height profile given the current gear settings
    createHeightProfile();
    for (int i = 0; i < Z_DETAIL_LEVEL; i++) {
        float z = i * dz;
        glm::vec4 a, b, c, d, norm;
        a.z = z;
        a.w = 1.0f;

        b.z = z;
        b.w = 1.0f;

        c.z = z + dz;
        c.w = 1.0f;

        d.z = z + dz;
        d.w = 1.0f;
        for (unsigned int segmentNum = 0; segmentNum < heightProfile_.size()-1;
                segmentNum++) {

            a.x = heightProfile_[segmentNum + 1].x;
            a.y = heightProfile_[segmentNum + 1].y;

            b.x = heightProfile_[segmentNum].x;
            b.y = heightProfile_[segmentNum].y;

            c.x = heightProfile_[segmentNum].x;
            c.y = heightProfile_[segmentNum].y;

            d.x = heightProfile_[segmentNum + 1].x;
            d.y = heightProfile_[segmentNum + 1].y;

            norm = glm::vec4(
                    glm::normalize(
                            glm::cross(glm::vec3(0.0f, 0.0f, c.z - b.z),
                                    glm::vec3(a.x - b.x, a.y - b.y, 0.0f))),
                    1.0f);

            vertexData_.push_back(a);
            //vertexData_.push_back(normNext);
            vertexData_.push_back(norm);
            vertexData_.push_back(b);
            vertexData_.push_back(norm);
            vertexData_.push_back(c);
            vertexData_.push_back(norm);
            vertexData_.push_back(d);
            //vertexData_.push_back(normNext);
            vertexData_.push_back(norm);
        }
    }

    return new QuadMesh(vertexData_);
}

TriangleMesh* BasicRack::toTriangleMesh() {
  //TODO: Implement this function
  return 0;
}
