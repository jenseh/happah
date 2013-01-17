#include "SceneManager.h"
#include <time.h>
#include "../test/WormGearGrindTest.h"

SceneManager::SceneManager() {
    // Load a few sample geometries
    Grid* grid = new Grid();
    Sphere* sphere = new Sphere(1.0f);
    SpurGear* gear1 = new SpurGear(1.0f, 1.0f, 20);//gears of radius 1 with 20 teeth are ~1.5 units away
    SpurGear* gear2 = new SpurGear(1.0f, 1.0f, 20);
    BasicRack* rack1 = new BasicRack(2.0f,  0.6f, 0.4f, 5);
    Disc* disc1 = new Disc();


    grid->setName("Grid");
    sphere->setName("Sphere");
    gear1->setName("Gear 1");
    gear2->setName("Gear 2");
    rack1->setName("Rack 1");
    disc1->setName("Disc 1");

    // Transform the original geometry for the simulation
//    gear1->translate(-0.1f, 0.0f, 0.0f);
//    gear1->rotate(-90.0f, 0.0f, 1.0f, 0.0f);
//    gear2->translate(0.0f, 0.0f, 0.5f);

    // Convert them to quad meshs
    grid_ = grid->toQuadMesh();
    sphere_ = sphere->toQuadMesh();
    gear1_ = gear1->toTriangleMesh();
//    gear2_ = gear2->toQuadMesh();
    rack1_ = rack1->toQuadMesh();
    disc1_ = disc1->toQuadMesh()->toTriangleMesh();

    // Transform the meshs for display
//    grid_->rotate(-45.0f, 0.0f, 0.0f, 1.0f);
//    grid_->rotate(-45.0f, 0.0f, 1.0f, 1.0f);
//    grid_->rotate(-45.0f, 1.0f, 0.0f, 1.0f);
//    grid_->rotate(-45.0f, 1.0f, 1.0f, 1.0f);
//    gear2_->rotate(45.0f, 0.0f, 0.0f, 1.0f);

    DiscGearGrind myGrind(disc1, gear1);
    vector<Color> colors = myGrind.calculateGrindingDepth();
//    std::cout<<colors.size()<<endl;
    /*for(size_t i = 0; i < colors.size(); i++){
        colors[i].red = 0;
        colors[i].blue = 0;
        colors[i].green = 1.0;
        colors[i].alpha = 1.0;
    }*/
    gear1_->setColorData(colors);

    // Add all quad meshs to a common vector
    drawables_ = new vector<Drawable*>();
    //drawables_->push_back(grid_);
//    drawables_->push_back(sphere_);
    drawables_->push_back(gear1_);
//    drawables_->push_back(gear2_);
    //drawables_->push_back(rack1_);
    drawables_->push_back(disc1_);

//    new WormGearGrindTest(gear1, gear2);
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
