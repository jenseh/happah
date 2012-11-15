#include "Gear.h"
#include <iostream>
#include <math.h>

using namespace std;

Gear::Gear(glm::vec3 _axisStart, float _radius, float _length, int _toothCount) {
    axisStart = _axisStart;
    radius = _radius;
    length = _length;
    toothCount = _toothCount;
}

Gear::~Gear() {
}

float Gear::getRadius(){
    return radius;
}

// Create a profile of height values
// x-values must be between 0 and 1 (position)
// y-values must be between -1 and 1 (height)
void Gear::createHeightProfile() {
    heightProfile = std::vector<glm::vec2>();

    for (int i = 0; i < SEGMENT_COUNT; i++) {
        float position = (float) i / (float)SEGMENT_COUNT;
        float height = 0.1f * sinf(position * 2.0f * 3.14f * toothCount) * radius;
        heightProfile.push_back(glm::vec2(position, height));
        //cout << position << ": " << height << std::endl;
    }
    // Add the first element again to close the "circle"
    heightProfile.push_back(heightProfile[0]);
}


// This creates the quads for a gear. The gear axis is the model's z-axis.
void Gear::CreateVertexData(){
    int dphi = 5;
    float dz = length;
    const float toRad = M_PI / 180.0f;

    // Create the height profile given the current gear settings
    createHeightProfile();

    // draw the sides (german: mantelflaechen) of the gear
    // this is the important part where the height profile will come into play
    float z = 0.0f;
        for (int segmentNum = 0; segmentNum < SEGMENT_COUNT; segmentNum++) {
            float phi = heightProfile[segmentNum].x * 360.0f;
            float nextPhi = heightProfile[segmentNum + 1].x * 360.0f;

            float height = heightProfile[segmentNum].y;
            float nextHeight = heightProfile[segmentNum + 1].y;

            glm::vec4 a, b, c, d, normA, normB, normC, normD;

            a.x = axisStart.x + cos(nextPhi * toRad) * (radius + nextHeight);
            a.y = axisStart.y + sin(nextPhi * toRad) * (radius + nextHeight);
            a.z = axisStart.z + z;
            a.w = 1.0f;
            normA = glm::normalize(a-glm::vec4(axisStart, 1.0f));

            b.x = axisStart.x + cos(phi * toRad) * (radius + height);
            b.y = axisStart.y + sin(phi * toRad) * (radius + height);
            b.z = axisStart.z + z;
            b.w = 1.0f;
            normB = glm::normalize(b-glm::vec4(axisStart, 1.0f));

            c.x = axisStart.x + cos(phi * toRad) * (radius + height);
            c.y = axisStart.y + sin(phi * toRad) * (radius + height);
            c.z = axisStart.z + z + dz;
            c.w = 1.0f;
            normC = glm::normalize(c-glm::vec4(axisStart + glm::vec3(0.0f, 0.0f, dz), 1.0f));

            d.x = axisStart.x + cos(nextPhi * toRad) * (radius + nextHeight);
            d.y = axisStart.y + sin(nextPhi * toRad) * (radius + nextHeight);
            d.z = axisStart.z + z + dz;
            d.w = 1.0f;
            normD = glm::normalize(d-glm::vec4(axisStart + glm::vec3(0.0f, 0.0f, dz), 1.0f));

            DataPushback(a);
            DataPushback(normA);
            DataPushback(b);
            DataPushback(normB);
            DataPushback(c);
            DataPushback(normC);
            DataPushback(d);
            DataPushback(normD);
    }

    // draw the front and back of the gear
    // this part is very straightforward. now alle quads have the
    // circle's center as a common point. for nicer highlights it
    // might be better to chose vertices in a more clever way.
    int i = 0;
    for (z = 0.0f; i < 2; i++, z += dz) {
        for (int segmentNum = 0; segmentNum < SEGMENT_COUNT - 1; segmentNum++) {
            float phi = heightProfile[segmentNum].x * 360.0f;
            float nextPhi = heightProfile[segmentNum + 1].x * 360.0f;
            float nextNextPhi = heightProfile[segmentNum + 2].x * 360.0f;

            float height = heightProfile[segmentNum].y;
            float nextHeight = heightProfile[segmentNum + 1].y;
            float nextNextHeight = heightProfile[segmentNum + 2].y;
            glm::vec4 a, b, c, d, normA, normB, normC, normD;

            a.x = axisStart.x + cos(phi * toRad) * (radius + height);
            a.y = axisStart.y + sin(phi * toRad) * (radius + height);
            a.z = axisStart.z + z;
            a.w = 1.0f;
            normA = glm::normalize(a-glm::vec4(axisStart + glm::vec3(0.0f, 0.0f, dz),1.0f));

            b.x = axisStart.x + cos(nextPhi * toRad) * (radius + nextHeight);
            b.y = axisStart.y + sin(nextPhi * toRad) * (radius + nextHeight);
            b.z = axisStart.z + z;
            b.w = 1.0f;
            normB = glm::normalize(b-glm::vec4(axisStart + glm::vec3(0.0f, 0.0f, dz),1.0f));

            c.x = axisStart.x + cos(nextNextPhi * toRad) * (radius + nextNextHeight);
            c.y = axisStart.y + sin(nextNextPhi * toRad) * (radius + nextNextHeight);
            c.z = axisStart.z + z;
            c.w = 1.0f;
            normC = glm::normalize(c-glm::vec4(axisStart + glm::vec3(0.0f, 0.0f, dz),1.0f));

            d.x = axisStart.x;
            d.y = axisStart.y;
            d.z = axisStart.z + z;
            d.w = 1.0f;
            normD = glm::normalize(d-glm::vec4(axisStart + glm::vec3(0.0f, 0.0f, dz),1.0f));

            DataPushback(a);
            DataPushback(normA);
            DataPushback(b);
            DataPushback(normB);
            DataPushback(c);
            DataPushback(normC);
            DataPushback(d);
            DataPushback(normD);
        }
    }
}

