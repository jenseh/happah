#ifndef DISCGEARGRIND_H
#define DISCGEARGRIND_H

#include <memory>
#include <map>

#include "happah/geometries/gears/SimpleGear.h"
#include "happah/kdtree/KDTree.h"
#include "happah/simulations/Simulation.h"
#include "happah/geometries/SurfaceOfRevolution.h"
#include "happah/simulations/Kinematic.h"


class DiscGearGrindResult : public SimulationResult {
public:
	SimpleGear_ptr m_gear;
	std::vector<hpcolor>* m_gearColor;
	TriangleMesh_ptr m_gearMesh;
	RigidAffineTransformation m_gearTransformation;
	SurfaceOfRevolution_ptr m_tool;
    hpcolor m_toolColor;
	TriangleMesh_ptr m_toolMesh;
	RigidAffineTransformation m_toolTransformation;


	DiscGearGrindResult(SimpleGear_ptr gear, vector<hpcolor>* gearColor, TriangleMesh_ptr gearMesh, RigidAffineTransformation gearTransformation,
						SurfaceOfRevolution_ptr tool, TriangleMesh_ptr toolMesh, RigidAffineTransformation toolTransformation):
		m_gear(gear),
		m_gearColor(new std::vector<hpcolor>(*gearColor) ), // Make copy !
		m_gearMesh(gearMesh),
		m_gearTransformation(gearTransformation),
		m_tool(tool),
        m_toolColor(hpvec4(0.5,0.5,0.5,1.0)),
		m_toolMesh(toolMesh),
		m_toolTransformation(toolTransformation){
	}
};


class DiscGearGrind : public Simulation
{

public:
    DiscGearGrind(SurfaceOfRevolution_ptr disc, TriangleMesh_ptr discMesh, SimpleGear_ptr gear, TriangleMesh_ptr gearMesh);
    ~DiscGearGrind();

    DiscGearGrindResult getSimulationResult(double time);
    void runSimulation();

private:
	static const int STEP_COUNT = 5;
	std::map< hpreal,DiscGearGrindResult> m_precalcResults;

    SurfaceOfRevolution_ptr m_disc;
    SimpleGear_ptr m_gear;

    TriangleMesh_ptr m_discMesh;
    vector<hpcolor>* m_gearColor;
    TriangleMesh_ptr m_gearMesh;
    std::vector<Ray>* m_gearRays;
    KDTree* m_kdTree;

    hpreal m_maxDistance;

    std::vector<double> m_distances;

    Kinematic m_gearMovement;

    void calculateGrindingDepth(double time);
    DiscGearGrindResult calculateSimulationResult(double time);
};

typedef std::shared_ptr<DiscGearGrind> DiscGearGrind_ptr;

#endif // DISCGEARGRIND_H
