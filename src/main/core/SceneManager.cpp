#include "SceneManager.h"

SceneManager::SceneManager() {
    // Load a few sample geometries
    Grid* grid = new Grid();
    Sphere* sphere = new Sphere(1.0f);
    SpurGear* gear1 = new SpurGear(1.0f, 1.0f, 20);
    SpurGear* gear2 = new SpurGear(0.5f, 1.0f, 10);
    BasicRack* rack1 = new BasicRack(2.0f,  0.6f, 0.4f, 5);
    Disc* disc1 = new Disc();


    grid->setName("Grid");
    sphere->setName("Sphere");
    gear1->setName("Gear 1");
    gear2->setName("Gear 2");
    rack1->setName("Rack 1");
    disc1->setName("Disc 1");


    // Convert them to quad meshs
    grid_ = grid->toQuadMesh();
    sphere_ = sphere->toQuadMesh();
    gear1_ = gear1->toTriangleMesh();
    gear2_ = gear2->toQuadMesh();
    rack1_ = rack1->toQuadMesh();
    disc1_ = disc1->toQuadMesh();


    // Do some rotation and translation
//    gear2_->translate(1.0f, 0.0f, 0.0f);
    grid_->rotate(-45.0f, 0.0f, 0.0f, 1.0f);
    grid_->rotate(-45.0f, 0.0f, 1.0f, 1.0f);
    grid_->rotate(-45.0f, 1.0f, 0.0f, 1.0f);
    grid_->rotate(-45.0f, 1.0f, 1.0f, 1.0f);
    gear2_->rotate(45.0f, 0.0f, 0.0f, 1.0f);



    // Add all quad meshs to a common vector
    drawables_ = new vector<Drawable*>();
    drawables_->push_back(grid_);
//    drawables_->push_back(sphere_);
//    drawables_->push_back(gear1_);
    drawables_->push_back(gear2_);
//    drawables_->push_back(rack1_);
//    drawables_->push_back(disc1_);

    // Run a simulation here, since keyEvents don't work yet..
    WormGearGrind* sim = new WormGearGrind(gear1, gear2);
    sim->runSimulation();

    // Test cases
//    Circle circle = Circle(glm::vec3(0, 0.0f, 0), glm::vec3(0, 1, 0), 1);
//    Triangle triangle = Triangle(glm::vec3(0, 1, 0), glm::vec3(0, 0, -1), glm::vec3(0, 0, 0));
//    bool result = circle.checkTriangleIntersection(&triangle);
//    std::cout << result << std::endl;

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
//    gear1_->rotate(1.0f, 0.0f, 0.0f, 1.0f);
//    gear2_->rotate(-2.0f, 0.0f, 0.0f, 1.0f);
}

vector<Drawable*>* SceneManager::getDrawables() {
    return drawables_;
}
