#include "WormGearGrindTest.h"

WormGearGrindTest::WormGearGrindTest() {
  // Run a simulation here for testing purposes
  InvoluteSpurGear* gear1 = new InvoluteSpurGear();//gears of radius 1 with 20 teeth are ~1.5 units away
  InvoluteSpurGear* gear2 = new InvoluteSpurGear();
  WormGearGrind* sim = new WormGearGrind(*gear1, *gear2);
  sim->runSimulation();
}
