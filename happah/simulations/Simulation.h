#ifndef SIMULATION_H
#define SIMULATION_H

#include <memory>

#include "happah/geometries/Mesh.h"
#include "happah/geometries/Geometry.h"
#include "happah/transformations/RigidAffineTransformation.h"
/**
 * @brief The SimulationResult class base class for all the different simulation results.
 */
class SimulationResult {};
/**
 * @brief The Simulation class is a general interface for any simulation.
 */
class Simulation
{
public:
	Simulation();
	virtual ~Simulation();
    /**
     * @brief runSimulation all the calculations of the simulation should be done in this method.
     */
    virtual void runSimulation() = 0;
    /**
     * @brief getToolVisible gets if the tool is visible to the user.
     * @returns visibility of the tool.
     */
    bool getToolVisibility()const;
    /**
     * @brief sets visibility of tool mesh in simulation.
     * @param visible visibility of tool.
     */
    void setToolVisibility(bool visible);

private:
    bool m_toolVisible;
};
typedef std::shared_ptr<Simulation> Simulation_ptr;

#endif // SIMULATION_H
