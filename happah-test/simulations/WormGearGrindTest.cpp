#include "happah-test/simulations/WormGearGrindTest.h"

WormGearGrindTest::WormGearGrindTest() {
  // Run a simulation here for testing purposes
  Worm* worm = new Worm();
  InvoluteGear* gear = new InvoluteGear(15, 0.13, 0.2, M_PI / 6.0, 0.0, 0.0, 0.0);
//  worm->translate(0.0, 2.0, 0.0);
//  gear->rotate(90.0, 0.0, 1.0, 0.0);
//  gear->translate(0.0f, -2.0, 0.0);

//  BasicRack* rack = new BasicRack();

//  TriangleMesh* wormMesh = worm->toTriangleMesh();
//  wormMesh->setMaterial(0.25, 0.5, 1.0, 10.0);
//  sceneManager->addDrawable(wormMesh);
//  sceneManager->addDrawable(gear->toTriangleMesh());
//  sceneManager->addDrawable(rack->toQuadMesh()->toTriangleMesh());
  RigidAffineTransformation trans1;
  RigidAffineTransformation trans2;
  WormGearGrind* sim = new WormGearGrind(*worm, *gear, trans1, trans2);
  sim->runSimulation();
}
