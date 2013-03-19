#ifndef DISCGEARGRIND_H
#define DISCGEARGRIND_H

#include <memory>

#include "happah/geometries/Disc.h"
#include "happah/geometries/SimpleGear.h"
#include "happah/kdtree/KDTree.h"
#include "happah/simulations/Simulation.h"
#include "happah/simulations/Kinematic.h"


class DiscGearGrindResult : public SimulationResult {
public:
	SimpleGear_ptr m_gear;
	vector<hpcolor>* m_gearColor;
	TriangleMesh_ptr m_gearMesh;
	RigidAffineTransformation m_gearTransformation;
	Disc_ptr m_tool;
	TriangleMesh_ptr m_toolMesh;
	RigidAffineTransformation m_toolTransformation;


	DiscGearGrindResult(SimpleGear_ptr gear, vector<hpcolor>* gearColor, TriangleMesh_ptr gearMesh, RigidAffineTransformation gearTransformation,
						Disc_ptr tool, TriangleMesh_ptr toolMesh, RigidAffineTransformation toolTransformation):
		m_gear(gear),
		m_gearColor(gearColor),
		m_gearMesh(gearMesh),
		m_gearTransformation(gearTransformation),
		m_tool(tool),
		m_toolMesh(toolMesh),
		m_toolTransformation(toolTransformation){
	}
};


class DiscGearGrind : public Simulation
{

public:
    DiscGearGrind(Disc_ptr disc, TriangleMesh_ptr discMesh, SimpleGear_ptr gear, TriangleMesh_ptr gearMesh);
    ~DiscGearGrind();

    DiscGearGrindResult getSimulationResult(double time);
    void runSimulation();

private:

    Disc_ptr m_disc;
    SimpleGear_ptr m_gear;

    TriangleMesh_ptr m_discMesh;
    vector<hpcolor>* m_gearColor;
    TriangleMesh_ptr m_gearMesh;
    std::vector<Ray>* m_gearRays;
    KDTree* m_kdTree;

    hpreal m_maxDistance;

    vector<double> m_distances;

    Kinematic m_gearMovement;

    void calculateGrindingDepth(double time);
};

typedef std::shared_ptr<DiscGearGrind> DiscGearGrind_ptr;

#endif // DISCGEARGRIND_H
