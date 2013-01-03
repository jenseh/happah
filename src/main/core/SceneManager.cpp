#include "SceneManager.h"

SceneManager::SceneManager() {
    // Load a few sample geometries
    Grid* grid = new Grid();
    Sphere* sphere = new Sphere(1.0f);
    SpurGear* gear1 = new SpurGear(1.0f, 1.0f, 20);
    SpurGear* gear2 = new SpurGear(0.5f, 1.0f, 10);
    BasicRack* rack1 = new BasicRack(2.0f,  0.6f, 0.4f, 5);

    grid->setName("Grid");
    sphere->setName("Sphere");
    gear1->setName("Gear 1");
    gear2->setName("Gear 2");
    rack1->setName("Rack 1");


    // Convert them to quad meshs
    grid_ = grid->toQuadMesh();
    sphere_ = sphere->toQuadMesh();
    gear1_ = gear1->toTriangleMesh();
    gear2_ = gear2->toQuadMesh();
    rack1_ = rack1->toQuadMesh();



    // Do some rotation and translation
    gear2_->translate(500.0f, 0.0f, 0.0f);
    gear2_->rotate(40.0f, 0.0f, 0.0f, 1.0f);



    // Add all quad meshs to a common vector
    drawables_ = new vector<Drawable*>();
    drawables_->push_back(grid_);
//    drawables_->push_back(sphere_);
    drawables_->push_back(gear1_);
//    drawables_->push_back(gear2_);
//    drawables_->push_back(rack1_);

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

vector<Drawable*>* SceneManager::getDrawables() {
    return drawables_;
}
