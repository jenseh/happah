#ifndef SIMULATION_H
#define SIMULATION_H

#include <memory>

#include "happah/geometries/Mesh.h"
#include "happah/geometries/Geometry.h"
#include "happah/transformations/RigidAffineTransformation.h"

class SimulationResult {

};

class Simulation
{
public:
	Simulation();
	virtual ~Simulation();

  virtual void runSimulation() = 0;
};

typedef std::shared_ptr<Simulation> Simulation_ptr;

#endif // SIMULATION_H
