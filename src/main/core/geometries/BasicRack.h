#ifndef BASICRACK_H
#define BASICRACK_H

#include <glm/glm.hpp>
#include <iostream>
#include <math.h>
#include "NonDrawable.h"
#include "BasicRack.h"
#include "StandardProfile.h"
#include "../models/QuadMesh.h"

using namespace std;


class BasicRack: public NonDrawable {
public:
    BasicRack(hpreal lenght = 2.0f, hpreal depth = 0.6f, hpreal height = 0.7f, int toothCount = 5);
    ~BasicRack();

    QuadMesh* toQuadMesh();
    TriangleMesh* toTriangleMesh();
private:
    hpreal height_; // Länge der Stange
    hpreal depth_; // Tiefe auf z Achse
    hpreal length_; // Länge
    int toothCount_; // Anzahl der Zähne
    hpreal module_; // Modul des Standartprofils
    std::vector<glm::vec2> heightProfilePartition_;
    std::vector<glm::vec2> heightProfile_;
    StandardProfile* standardProfile;
    std::vector<glm::vec4> vertexData_;

    const static int SEGMENT_COUNT = 40; //maximum: 4500
    const static int Z_DETAIL_LEVEL = 4;

    void createHeightProfilePartition();
    void createHeightProfile();
};

#endif // BASICRACK_H
