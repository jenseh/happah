#ifndef SIMULATION_H
#define SIMULATION_H

#include "happah/geometries/Geometry.h"

class SimulationResult{
};

class Simulation
{
public:
  virtual ~Simulation();

  virtual void runSimulation();
  virtual SimulationResult getDisplay(double time);
};

#endif // SIMULATION_H
