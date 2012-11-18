#ifndef GEAR_H
#define GEAR_H

#include <glm/glm.hpp>
#include "GeometryObject.h"

class Gear : public GeometryObject {
public:
    Gear(float _radius = 1.0f, float _length = 0.2f, int toothCount = 10, float heightFactor = 0.2f);
    virtual ~Gear();
    float getRadius();
    glm::vec3 getCenter();
    void CreateVertexData();
private:
    float radius;
    float length;
    int toothCount;
    float heightFactor;
    std::vector<glm::vec2> heightProfilePartition;
    std::vector<glm::vec2> heightProfile;

    const static int SEGMENT_COUNT = 40; //maximum: 4500
    const static int Z_DETAIL_LEVEL = 4;
    const static float INNER_RADIUS_FACTOR = 0.5f;

    void createSinePartition();
    void createApproximatedPartition();
    void createHeightProfilePartition();
    void createHeightProfile();
};

#endif // GEAR_H
