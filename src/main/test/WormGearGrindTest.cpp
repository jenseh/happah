#include "WormGearGrindTest.h"

WormGearGrindTest::WormGearGrindTest(SceneManager* sceneManager) {
  // Run a simulation here for testing purposes
  InvoluteSpurGear* worm = new InvoluteSpurGear(30, 0.13f, 0.2f, M_PI / 6.0f, 0.00f, 0.00f, "Worm");
  InvoluteSpurGear* gear = new InvoluteSpurGear(15, 0.13f, 0.2f, M_PI / 6.0f, 0.00f, 0.00f, "Gear");
  worm->translate(0.0f, 2.0f, 0.0f); //TODO:remove
  gear->translate(0.0f, -2.0f, 0.0f); //TODO:remove
  sceneManager->addDrawable(worm->toTriangleMesh());
  sceneManager->addDrawable(gear->toTriangleMesh());
//  WormGearGrind* sim = new WormGearGrind(*worm, *gear);
//  sim->runSimulation();
}
