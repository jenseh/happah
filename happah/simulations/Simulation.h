#ifndef SIMULATION_H
#define SIMULATION_H

#include "happah/models/Drawable.h"

class Simulation
{
public:
  virtual ~Simulation();

  virtual void runSimulation();
  virtual Drawable* getDisplay(double time);
};

#endif // SIMULATION_H
