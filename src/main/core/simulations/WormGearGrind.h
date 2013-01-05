#ifndef WORMGEARGRIND_H
#define WORMGEARGRIND_H

#include "../geometries/SpurGear.h"

class WormGearGrind
{
public:
  WormGearGrind(SpurGear* worm, SpurGear* gear);
  ~WormGearGrind();

  void runSimulation();
  void calculateGrindingDepth();

private:
  SpurGear* m_worm;
  SpurGear* m_gear;

  const static float MAX_DIST = 1.0f;
};

#endif // WORMGEARGRIND_H
