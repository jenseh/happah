#ifndef SIMULATIONLISTENER_H_
#define SIMULATIONLISTENER_H_

#include "happah/simulations/Simulation.h"

class SimulationListener {

public:
	virtual void insert(SimulationResult simulationResult) = 0;
	virtual void update(SimulationResult simulationResult) = 0;
};


#endif /* SIMULATIONLISTENER_H_ */
