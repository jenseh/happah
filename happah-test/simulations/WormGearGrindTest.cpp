#include "happah-test/simulations/WormGearGrindTest.h"

WormGearGrindTest::WormGearGrindTest() {
  // Run a simulation here for testing purposes
  Worm* worm = new Worm();
  InvoluteGear* gear = new InvoluteGear();

//  BasicRack* rack = new BasicRack();
  RigidAffineTransformation trans1;
  RigidAffineTransformation trans2;
  WormGearGrind* sim = new WormGearGrind(*worm, *gear, trans1, trans2);
  sim->runSimulation();
}
