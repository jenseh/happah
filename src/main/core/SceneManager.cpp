#include "SceneManager.h"

SceneManager::SceneManager() {
    // Load a few sample geometries
    Grid* grid = new Grid();
    Sphere* sphere = new Sphere(1.0f);
    Gear* gear1 = new Gear(1.0f, 1.0f, 20);
    Gear* gear2 = new Gear(0.5f, 1.0f, 10);
    BasicRack* rack1 = new BasicRack(2.0f,  0.6f, 0.4f, 5);

    // Load their internal representation
    grid->createVertexData();
    sphere->createVertexData();
    gear1->createVertexData();
    gear2->createVertexData();
    rack1->createVertexData();

    // Convert them to quad meshs
    grid_ = grid->toQuadrilateralMesh();
    sphere_ = sphere->toQuadrilateralMesh();
    gear1_ = gear1->toQuadrilateralMesh();
    gear2_ = gear2->toQuadrilateralMesh();
    rack1_ = rack1->toQuadrilateralMesh();

    // Do some rotation and translation
    gear2_->translate(1.9f, 0.0f, 0.0f);
    gear2_->rotate(40.0f, 0.0f, 0.0f, 1.0f);

    // Add all quad meshs to a common vector
    quadliteralMeshs_.push_back(grid_);
    //quadliteralMeshs_.push_back(sphere_);
    //quadliteralMeshs_.push_back(gear1_);
    //quadliteralMeshs_.push_back(gear2_);
    quadliteralMeshs_.push_back(rack1_);

    //TODO: Setup and start a timer
//    timer_ = new QTimer();
//    connect(timer_, SIGNAL(timeout()), this, SLOT(update()));
//    timer_->start(WAIT_TIME);
}

SceneManager::~SceneManager() {

}

// This method updates the simulation
void SceneManager::update() {
    // modify the model
    gear1_->rotate(1.0f, 0.0f, 0.0f, 1.0f);
    gear2_->rotate(-2.0f, 0.0f, 0.0f, 1.0f);
}

vector<QuadliteralMesh*> SceneManager::getQuadliteralMeshs() {
    return quadliteralMeshs_;
}
