#ifndef DISCGEARGRIND_H
#define DISCGEARGRIND_H

#include <memory>

#include "happah/geometries/Disc.h"
#include "happah/geometries/Gear.h"
#include "happah/kdtree/KDTree.h"
#include "happah/simulations/Simulation.h"
#include "happah/simulations/Kinematic.h"


class DiscGearGrind : public Simulation
{

public:
    DiscGearGrind(Disc_ptr disc, Gear_ptr gear);
    ~DiscGearGrind();

    SimulationResult getSimulationResult(double time);
    void runSimulation();

private:

    Disc_ptr m_disc;
    Gear_ptr m_gear;

    TriangleMesh_ptr m_discMesh;
    vector<hpcolor>* m_gearColor;
    TriangleMesh_ptr m_gearMesh;
    std::vector<Ray>* m_gearRays;
    KDTree* m_kdTree;

    hpreal m_maxDistance;

    vector<double> m_distances;

    Kinematic m_gearMouvement;

    void calculateGrindingDepth(double time);
};

typedef std::shared_ptr<DiscGearGrind> DiscGearGrind_ptr;

#endif // DISCGEARGRIND_H
