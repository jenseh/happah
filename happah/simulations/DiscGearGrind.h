#ifndef DISCGEARGRIND_H
#define DISCGEARGRIND_H

#include "happah/geometries/Disc.h"
#include "happah/geometries/Gear.h"
#include "happah/kdtree/KDTree.h"
#include "happah/simulations/Kinematic.h"

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
    std::vector<Ray>* m_gearRays;
    KDTree* m_kdTree;

    vector<double> m_distances;

    Kinematic m_gearMouvement;

    void calculateGrindingDepth(double time);
};

#endif // DISCGEARGRIND_H
