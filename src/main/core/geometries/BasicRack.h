#ifndef BASICRACK_H
#define BASICRACK_H

#include <glm/glm.hpp>
#include <iostream>
#include <math.h>
#include "NonDrawable.h"
#include "BasicRack.h"
#include "StandardProfile.h"

using namespace std;


class BasicRack: public NonDrawable {
public:
    BasicRack(float lenght = 2.0f, float depth = 0.6f, float height = 0.7f, int toothCount = 5);

    virtual ~BasicRack();
    void createVertexData();
private:
    float height_; // Länge der Stange
    float depth_; // Tiefe auf z Achse
    float length_; // Länge
    int toothCount_; // Anzahl der Zähne
    float module_; // Modul des Standartprofils
    std::vector<glm::vec2> heightProfilePartition_;
    std::vector<glm::vec2> heightProfile_;
    StandardProfile* standardProfile;

    const static int SEGMENT_COUNT = 40; //maximum: 4500
    const static int Z_DETAIL_LEVEL = 4;

    void createHeightProfilePartition();
    void createHeightProfile();
};

#endif // BASICRACK_H
