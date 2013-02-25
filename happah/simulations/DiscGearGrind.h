#ifndef DISCGEARGRIND_H
#define DISCGEARGRIND_H

#include "../geometries/Disc.h"
#include "../geometries/Gear.h"
#include "../kdtree/TriangleKDTree.h"
#include "../primitives/Color.h"
#include "Kinematic.h"

class DiscGearGrind
{
public:
    DiscGearGrind(Disc* disc, Gear* gear);
    ~DiscGearGrind();

    pair<TriangleMesh*,TriangleMesh*> getDisplay(double time);

private:
    Disc* m_disc;
    Gear* m_gear;

    TriangleMesh* m_discMesh;
    TriangleMesh* m_gearMesh;
    std::vector<Ray*> m_gearRays;
    TriangleKDTree m_kdTree;

    vector<double> m_distances;

    Kinematic m_gearMouvement;

    void calculateGrindingDepth(double time);
};

#endif // DISCGEARGRIND_H
