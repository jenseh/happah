#ifndef BASICRACK_H
#define BASICRACK_H

#include <glm/glm.hpp>
#include <iostream>
#include <math.h>
#include "happah/geometries/gears/BasicRack.h"
#include "happah/geometries/gears/StandardProfile.h"
#include "happah/geometries/Mesh.h"

class BasicRack{
public:
    BasicRack(hpreal length = 2.0f,
              hpreal depth = 0.6f,
              hpreal height = 0.7f,
              hpuint toothCount = 5);
    ~BasicRack();

    //QuadMesh* toQuadMesh();
    TriangleMesh* toTriangleMesh();
private:
    hpreal m_height; // Länge der Stange
    hpreal m_depth; // Tiefe auf z Achse
    hpreal m_length; // Länge
    hpuint m_toothCount; // Anzahl der Zähne
    hpreal m_module; // Modul des Standartprofils
    StandardProfile* m_standardProfile;

    const static int SEGMENT_COUNT = 40; //maximum: 4500
    const static int Z_DETAIL_LEVEL = 4;

    void createHeightProfilePartition();
    void createHeightProfile();
    std::vector<hpvec3>* createVertexData();
};

#endif // BASICRACK_H
