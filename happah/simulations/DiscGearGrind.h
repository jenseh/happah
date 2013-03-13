#ifndef DISCGEARGRIND_H
#define DISCGEARGRIND_H

#include "happah/geometries/Disc.h"
#include "happah/geometries/Gear.h"
#include "happah/kdtree/KDTree.h"
#include "happah/simulations/Simulation.h"
#include "happah/simulations/Kinematic.h"

class DiscGearGrindResult: public SimulationResult{
public:
	vector<hpcolor>* m_discColor;
	TriangleMesh* m_discMesh;
	TriangleMesh* m_gearMesh;

	DiscGearGrindResult(TriangleMesh* gearMesh, TriangleMesh* discMesh, vector<hpcolor>* discColor):
		m_gearMesh(gearMesh), m_discMesh(discMesh), m_discColor(discColor){

	}
};

class DiscGearGrind
{

public:
    DiscGearGrind(Disc* disc, Gear* gear);
    ~DiscGearGrind();

    DiscGearGrindResult getDisplay(double time);

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
