#ifndef BASICRACK_H
#define BASICRACK_H

#include <glm/glm.hpp>
#include <iostream>
#include <math.h>
#include "happah/geometries/NonDrawable.h"
#include "happah/geometries/BasicRack.h"
#include "happah/geometries/StandardProfile.h"
#include "happah/geometries/QuadMesh.h"

using namespace std;


class BasicRack: public NonDrawable {
public:
    BasicRack(hpreal length = 2.0f,
              hpreal depth = 0.6f,
              hpreal height = 0.7f,
              int toothCount = 5,
              std::string name = "BasicRack");
    ~BasicRack();

    QuadMesh* toQuadMesh();
    TriangleMesh* toTriangleMesh();
private:
    hpreal m_height; // Länge der Stange
    hpreal m_depth; // Tiefe auf z Achse
    hpreal m_length; // Länge
    int m_toothCount; // Anzahl der Zähne
    hpreal m_module; // Modul des Standartprofils
    std::vector<glm::vec2> m_heightProfilePartition;
    std::vector<glm::vec2> m_heightProfile;
    StandardProfile* m_standardProfile;
    std::vector<glm::vec4> m_vertexData;

    const static int SEGMENT_COUNT = 40; //maximum: 4500
    const static int Z_DETAIL_LEVEL = 4;

    void createHeightProfilePartition();
    void createHeightProfile();
};

#endif // BASICRACK_H
