#ifndef WORMGEARGRIND_H
#define WORMGEARGRIND_H

#include <time.h>
#include <memory>
#include <map>

#include "happah/HappahTypes.h"
#include "happah/geometries/gears/InvoluteGear.h"
#include "happah/geometries/gears/Worm.h"
#include "happah/geometries/ZCircleCloud.h"
#include "happah/kdtree/KDTree.h"
#include "happah/math/Circle.h"
#include "happah/math/Triangle.h"
#include "happah/simulations/CircularSimulationResult.h"
#include "happah/simulations/Kinematic.h"
#include "happah/simulations/Simulation.h"
#include "happah/transformations/RigidAffineTransformation.h"

/**
 * @brief The WormGearGrindResult class bundles all the information needed to display a worm gear grind simulation to a given time.
 */
class WormGearGrindResult : public SimulationResult {
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
     * @brief m_tool Worm representing the tool used to grind the gear.
     */
	Worm_ptr m_tool;
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
     * @brief WormGearGrindResult sets all the member variables.
     * @param gear The gear of the simulation.
     * @param gearColor Vector with the color data of the gear.
     * @param gearMesh The triangle mesh representing the gear.
     * @param gearTransformation The position/transformation of the gear.
     * @param tool Worm representing the tool used to grind the gear.
     * @param toolMesh The triangle mesh mesh representing the tool.
     * @param toolTransformation The position/transformation of the tool.
     */
	WormGearGrindResult(SimpleGear_ptr gear, vector<hpcolor>* gearColor, TriangleMesh_ptr gearMesh, RigidAffineTransformation gearTransformation,
						Worm_ptr tool, TriangleMesh_ptr toolMesh, RigidAffineTransformation toolTransformation):
		m_gear(gear),
        m_gearColor(new std::vector<hpcolor>(*gearColor)),
		m_gearMesh(gearMesh),
		m_gearTransformation(gearTransformation),
		m_tool(tool),
        m_toolColor(hpvec4(0.95, 0.4, 0.4, 1.0)),
		m_toolMesh(toolMesh),
		m_toolTransformation(toolTransformation){
	}
};

class WormGearGrind : public Simulation
{
public:
//  WormGearGrind(Worm_ptr worm, TriangleMesh_ptr wormMesh, InvoluteGear_ptr gear, TriangleMesh_ptr gearMesh);
  WormGearGrind(Worm_ptr worm, TriangleMesh_ptr wormMesh, SimpleGear_ptr gear, hpreal gearReferenceRadius, TriangleMesh_ptr gearMesh);

  ~WormGearGrind();

  WormGearGrindResult calculateSimulationResult(hpreal time);

  /**
   * @brief getSimulationResult returns the simulation result at a certain time.
   *        There are only discrete number of time step pre-calculated, so the latest result before time is returned.
   * @param time The time of the simulation result ( time has to be in the interval [0,1] ).
   * @return The simulation result with all the information needed to display the simulation at the given time.
   */

  WormGearGrindResult getSimulationResult(hpreal time);

  void runSimulation();
  CircularSimulationResult* calculateGrindingDepth(hpreal time);

private:
  void init(hpreal gearReferenceRadius);

  void inline computeIntersectingTriangles(hpuint& wormPosZIdx, CircularSimulationResult* simResult, hpmat4x4& gearModelMatrix, hpmat4x4& wormModelMatrix, hpreal& time);

  Circle inline transformCircle(Circle& circle, hpmat4x4 transformation);
  hpvec3 inline transformPoint(hpvec3& point, hpmat4x4& transformation);
  hpvec3 inline transformVector(hpvec3& vector, hpmat4x4& transformation);
  Triangle translateTriangle(Triangle& triangle, hpvec3& vector);

private:
	/**
	 * @brief STEP_COUNT Number of time steps calculated for the simulation ( eg. if STEP_COUNT = 3 then steps t = 0, t = 0.5, t = 1 are calculated ).
	 */
	static const int STEP_COUNT = 20;

	Worm_ptr m_worm;
	TriangleMesh_ptr m_wormMesh;

	SimpleGear_ptr m_gear;
	vector<hpcolor>* m_gearColor;
	TriangleMesh_ptr m_gearMesh;
	ZCircleCloud_ptr m_gearCircleCloud;

	Kinematic m_gearMovement;
	Kinematic m_wormMovement;
	KDTree* m_kdTree;
	hpreal m_maxDistance;
	std::map<hpreal, WormGearGrindResult> m_precalcResults;

	constexpr static size_t m_resultAngleSlotCount = 10;
	constexpr static size_t m_resultPosZSlotCount = 10;

};

typedef std::shared_ptr<WormGearGrind> WormGearGrind_ptr;

#endif // WORMGEARGRIND_H
