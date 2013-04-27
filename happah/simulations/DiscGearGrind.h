#ifndef DISCGEARGRIND_H
#define DISCGEARGRIND_H

#include <memory>
#include <map>

#include "happah/geometries/gears/SimpleGear.h"
#include "happah/geometries/SurfaceOfRevolution.h"
#include "happah/kdtree/KDTree.h"
#include "happah/simulations/Kinematic.h"
#include "happah/simulations/Simulation.h"

/**
 * @brief The DiscGearGrindResult class bundles all the information needed to display a disc gear grind simulation to a given time.
 */
class DiscGearGrindResult : public SimulationResult {
public:
    /**
     * @brief m_gear The gear of the simulation.
     */
	SimpleGear_ptr m_gear;
    /**
     * @brief m_gearColor Vector with the color data of the gear.
     */
	std::vector<hpcolor>* m_gearColor;
    /**
     * @brief m_gearMesh  The triangle mesh representing the gear.
     */
	TriangleMesh_ptr m_gearMesh;
    /**
     * @brief m_gearTransformation The position/transformation of the gear.
     */
	RigidAffineTransformation m_gearTransformation;
    /**
     * @brief m_tool Surface of revolution representing the tool used to grind the gear.
     */
	SurfaceOfRevolution_ptr m_tool;
    /**
     * @brief m_toolColor The unified color of the tool.
     */
    hpcolor m_toolColor;
    /**
     * @brief m_toolMesh The triangle mesh representing the tool.
     */
	TriangleMesh_ptr m_toolMesh;
    /**
     * @brief m_toolTransformation The position/transformation of the tool.
     */
	RigidAffineTransformation m_toolTransformation;

    /**
     * @brief DiscGearGrindResult sets all the member variables.
     * @param gear The gear of the simulation.
     * @param gearColor Vector with the color data of the gear.
     * @param gearMesh The triangle mesh representing the gear.
     * @param gearTransformation The position/transformation of the gear.
     * @param tool Surface of revolution representing the tool used to grind the gear.
     * @param toolMesh The triangle mesh representing the tool.
     * @param toolTransformation The position/transformation of the tool.
     */
	DiscGearGrindResult(SimpleGear_ptr gear, vector<hpcolor>* gearColor, TriangleMesh_ptr gearMesh, RigidAffineTransformation gearTransformation,
						SurfaceOfRevolution_ptr tool, TriangleMesh_ptr toolMesh, RigidAffineTransformation toolTransformation):
		m_gear(gear),
        m_gearColor(new std::vector<hpcolor>(*gearColor) ),
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
    /**
     * @brief DiscGearGrind constructor doing some minor precalculations for the simulation.
     * @param disc The disc which is used to grind the gear in the simulation.
     * @param discMesh The triangle mesh representing the disc.
     * @param gear The gear which is grinded by the gear in the simulation.
     * @param gearMesh The triangle mesh representing the gear.
     */
    DiscGearGrind(SurfaceOfRevolution_ptr disc, TriangleMesh_ptr discMesh, SimpleGear_ptr gear, TriangleMesh_ptr gearMesh);
    /**
     * @brief ~DiscGearGrind Destructor deleting memory which was allocated for the calculation of the simulation.
     */
    ~DiscGearGrind();


    /**
     * @brief getSimulationResult returns the simulation result at a certain time.
     *        There are only discrete number of time step precalculated, so the latest result before time is returned.
     * @param time The time of the simulation result ( time has to be in the interval [0,1] ).
     * @return The simulation result with all the information needed to display the simulation at the given time.
     */
    DiscGearGrindResult getSimulationResult(hpreal time);
    /**
     * @brief runSimulation precalculates the STEP_COUNT simulation steps and stores them in private member m_precalcResults.
     */
    void runSimulation();

private:
    /**
     * @brief STEP_COUNT Number of time steps calculated for the simulation ( eg. if STEP_COUNT = 3 then steps t = 0, t = 0.5, t = 1 are calculated ).
     */
	static const int STEP_COUNT = 1;

    SurfaceOfRevolution_ptr m_disc;
    TriangleMesh_ptr m_discMesh;
    std::vector<double> m_distances;
    SimpleGear_ptr m_gear;
    vector<hpcolor>* m_gearColor;
    TriangleMesh_ptr m_gearMesh;
    Kinematic m_gearMovement;
    std::vector<Ray>* m_gearRays;
    KDTree* m_kdTree;
    hpreal m_maxDistance;
    std::map<hpreal,DiscGearGrindResult> m_precalcResults;
    /**
     * @brief calculateGrindingDepth calculated the distances from each vertex of the gear ( m_gearRays ) to the disc and stores them in m_distances.
        For the calculation the rays of the gear with the vertexes as origin and normals as direction are intersected with the disc mesh.
     * @param time The position in time to which the distances are suppose to be calculated.
     */
    void calculateGrindingDepth(double time);
    /**
     * @brief calculateSimulationResult uses calculateGrindingDepth to calculate the colors of the disc and returns all the information as DiscGearGrindSimulationResult.
     * @param time The point in time to which the simulation result is calculated.
     * @return Returns all the information representing the simulation to the given time.
     */
    DiscGearGrindResult calculateSimulationResult(double time);
};

typedef std::shared_ptr<DiscGearGrind> DiscGearGrind_ptr;

#endif // DISCGEARGRIND_H
