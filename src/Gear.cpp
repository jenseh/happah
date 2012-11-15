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

void Gear::createSinePartition() {
    // Use this to draw a sinus surface
    for (int i = 0; i < SEGMENT_COUNT; i++) {
        float position = (float) i / (float) SEGMENT_COUNT;
        float height = exp2f(sinf(position * 2.0f * M_PI));
        heightProfilePartition.push_back(glm::vec2(position, height));
        //cout << position << ": " << height << std::endl;
   }
}

void Gear::createApproximatedPartition() {
    const int segmentsPerLine = SEGMENT_COUNT / 5;

    float horizX = 0.35f; //check whether 2*horiz + 2*flankX = 1.0
    float flankX = 0.15f;

    // Use this to draw a gear with straight flanks and a quadratic bottom
    // horizontal teeth part
    for (int i = 0; i < segmentsPerLine; i++) {
        float x = (float) i / segmentsPerLine;
        heightProfilePartition.push_back(glm::vec2(0.0f + x * horizX, 1.0f));
    }

    // right flank
    for (int i = 0; i < segmentsPerLine; i++) {
        float x = (float) i / segmentsPerLine;
        heightProfilePartition.push_back(glm::vec2(horizX + x * flankX, 1.0f - x * 0.8f));
    }

    // lower teeth part
    // fit a quadratic function for the bottom part of a teeth hole
    for (int i = 0; i < segmentsPerLine; i++) {
                    float x = (float) i / segmentsPerLine;
                    float position = horizX + flankX + x * horizX;
                    float height = 0.2f * pow(2.0f * x - 1.0f, 2.0f);
                    heightProfilePartition.push_back(glm::vec2(position, height));
                    //cout << position << ": " << height << std::endl;
    }

    //left flank
    for (int i = 0; i < segmentsPerLine; i++) {
        float x = (float) i / segmentsPerLine;
        heightProfilePartition.push_back(glm::vec2(horizX + flankX + horizX + x * flankX, 0.2f + x * 0.8f));
    }
}

// Create a profile of height values for one partition (german: Teilung)
// x-values must be between 0 and 1 (position)
// y-values must be between -1 and 1 (height)
void Gear::createHeightProfilePartition() {
    heightProfilePartition = std::vector<glm::vec2>();

    createApproximatedPartition();
}

// Create a profile of height values
// x-values must be between 0 and 1 (position)
// y-values must be between -1 and 1 (height)
void Gear::createHeightProfile() {
    createHeightProfilePartition();
    heightProfile = std::vector<glm::vec2>();

    for (int i = 0; i < toothCount; i++) {
        for (unsigned int j = 0; j < heightProfilePartition.size(); j++) {
            float position = (heightProfilePartition[j].x + i) / toothCount;
            float height = heightProfilePartition[j].y;
            heightProfile.push_back(glm::vec2(position, height));
            //cout << position << ": " << height << std::endl;
        }
    }
    // Add the first element again to close the "circle"
    // TODO: Rethink whether this makes sense
    heightProfile.push_back(heightProfile[0]);
}


// This creates the quads for a gear. The gear axis is the model's z-axis.
void Gear::CreateVertexData(){
    float dz = length;
    const float toRad = M_PI / 180.0f;
    const float heightFactor = 0.2f;

    // Create the height profile given the current gear settings
    createHeightProfile();

    // draw the sides (german: Mantelflaechen) of the gear
    // this is the important part where the height profile will come into play
    float z = 0.0f;
        for (unsigned int segmentNum = 0; segmentNum < heightProfile.size(); segmentNum++) {
            float phi = heightProfile[segmentNum].x * 360.0f;
            float nextPhi = heightProfile[segmentNum + 1].x * 360.0f;

            float height = heightProfile[segmentNum].y * heightFactor * radius;
            float nextHeight = heightProfile[segmentNum + 1].y * heightFactor * radius;

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
        for (unsigned int segmentNum = 0; segmentNum < heightProfile.size() - 1; segmentNum++) {
            float phi = heightProfile[segmentNum].x * 360.0f;
            float nextPhi = heightProfile[segmentNum + 1].x * 360.0f;
            float nextNextPhi = heightProfile[segmentNum + 2].x * 360.0f;

            float height = heightProfile[segmentNum].y * heightFactor * radius;
            float nextHeight = heightProfile[segmentNum + 1].y * heightFactor * radius;
            float nextNextHeight = heightProfile[segmentNum + 2].y * heightFactor * radius;
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

