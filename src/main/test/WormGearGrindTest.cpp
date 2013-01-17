#include "WormGearGrindTest.h"

WormGearGrindTest::WormGearGrindTest(SpurGear* gear1, SpurGear* gear2) {
  // Run a simulation here for testing purposes
  WormGearGrind* sim = new WormGearGrind(*gear1, *gear2);
  sim->runSimulation();
}
