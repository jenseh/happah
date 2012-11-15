#ifndef GEAR_H
#define GEAR_H

#include <glm/glm.hpp>
#include "GeometryObject.h"

class Gear : public GeometryObject {
public:
    Gear(glm::vec3 _axisStart = glm::vec3(0.0f, 0.0f, 0.0f), float _radius = 1.0f, float _length = 0.2f, int toothCount = 10);
    virtual ~Gear();
    float getRadius();
    glm::vec3 getCenter();
    void CreateVertexData();
private:
    glm::vec3 axisStart;
    float radius;
    float length;
    int toothCount;
    std::vector<glm::vec2> heightProfile;

    const static int SEGMENT_COUNT = 500;

    void createHeightProfile();
};

#endif // GEAR_H
