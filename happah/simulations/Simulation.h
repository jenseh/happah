#ifndef SIMULATION_H
#define SIMULATION_H

#include "happah/geometries/Geometry.h"

class Simulation
{
public:
  virtual ~Simulation();

  virtual void runSimulation();
  virtual Geometry* getDisplay(double time);
};

#endif // SIMULATION_H
