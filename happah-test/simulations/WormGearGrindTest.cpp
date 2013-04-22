#include "happah-test/simulations/WormGearGrindTest.h"

WormGearGrindTest::WormGearGrindTest() {
  // Run a simulation here for testing purposes
  Worm_ptr worm = Worm_ptr(new Worm());
  InvoluteGear_ptr gear = InvoluteGear_ptr(new InvoluteGear());

  TriangleMesh_ptr wormMesh = TriangleMesh_ptr(worm->toTriangleMesh());
  TriangleMesh_ptr gearMesh = TriangleMesh_ptr(gear->toTriangleMesh());

  WormGearGrind* sim = new WormGearGrind(worm, wormMesh, gear, gearMesh);
  sim->runSimulation();
}
