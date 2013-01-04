#ifndef WORMGEARGRIND_H
#define WORMGEARGRIND_H

#include "../geometries/SpurGear.h"

class WormGearGrind
{
public:
  WormGearGrind(SpurGear* worm, SpurGear* gear);
  ~WormGearGrind();

  void calculateGrindingDepth();
};

#endif // WORMGEARGRIND_H
