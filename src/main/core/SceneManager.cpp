#include "SceneManager.h"
#include <time.h>

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
//    gear1->translate(-1.5f, 0.0f, 0.0f);
//    gear1->rotate(-90.0f, 0.0f, 1.0f, 0.0f);
//    gear2->translate(0.0f, 0.0f, 0.5f);

    // Convert them to quad meshs
    grid_ = grid->toQuadMesh();
    sphere_ = sphere->toQuadMesh();
    gear1_ = gear1->toTriangleMesh();
//    gear2_ = gear2->toQuadMesh();
    rack1_ = rack1->toQuadMesh();
    disc1_ = disc1->toQuadMesh();

    // Transform the meshs for display
//    grid_->rotate(-45.0f, 0.0f, 0.0f, 1.0f);
//    grid_->rotate(-45.0f, 0.0f, 1.0f, 1.0f);
//    grid_->rotate(-45.0f, 1.0f, 0.0f, 1.0f);
//    grid_->rotate(-45.0f, 1.0f, 1.0f, 1.0f);
//    gear2_->rotate(45.0f, 0.0f, 0.0f, 1.0f);

//    DiscGearGrind myGrind(disc1, gear1);
//    vector<Color> colors = myGrind.calculateGrindingDepth();
//    std::cout<<colors.size()<<endl;
//    for(size_t i = 0; i < colors.size(); i++){
//        colors[i].red = 0;
//        colors[i].blue = 0;
//        colors[i].green = 1.0;
//        colors[i].alpha = 1.0;
//      }
//    gear1_->setColorData(colors);

    // Add all quad meshs to a common vector
    drawables_ = new vector<Drawable*>();
    //drawables_->push_back(grid_);
//    drawables_->push_back(sphere_);
    drawables_->push_back(gear1_);
//    drawables_->push_back(gear2_);
//    drawables_->push_back(rack1_);
//    drawables_->push_back(disc1_);

    // Run a simulation here for testing purposes
//    WormGearGrind* sim = new WormGearGrind(*gear1, *gear2);
//    sim->runSimulation();

    // Test cases
//    int maxCount = 0;
//    Triangle triangle = Triangle(glm::vec3(0.0f, 1.0f, 0.0f),
//                                 glm::vec3(-1.0f, 0.0f, 0.0f),
//                                 glm::vec3(1.0f, 0.0f, 0.0f));
//    {
//      std::cout << "Running ZCircle benchmark:" << std::endl;
//      ZCircle circle = ZCircle(0.5f);
//      Triangle transformedTriangle = WormGearGrind(*gear1, *gear2).transformTriangle(triangle);
////      std::cout << "Transformation-A: " << triangle.vertices[0].x << ", " << triangle.vertices[0].y << ", " << triangle.vertices[0].z << " to " << transformedTriangle.vertices[0].x << ", " << transformedTriangle.vertices[0].y << ", " << transformedTriangle.vertices[0].z << std::endl;

//      clock_t start, end;
//      start = clock();
//      bool result;
//      for (int count = 0; count < maxCount; count++) {
//        result = circle.checkTriangleIntersection(transformedTriangle);
//      }
//      end = clock();
//      double totalTime = (double)(end-start)/CLOCKS_PER_SEC;
//      std::cout << "Result: " << result << std::endl;
//      std::cout << "Time: " << totalTime/maxCount << ", total: " << totalTime << " seconds." << std::endl;
//    }




//    {
//      std::cout << "Running Circle benchmark:" << std::endl;
//      Circle circle = Circle(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), 0.5f);
//      Triangle transformedTriangle = WormGearGrind(*gear1, *gear2).transformTriangle(triangle);
////      std::cout << "Transformation-A: " << triangle.vertices[0].x << ", " << triangle.vertices[0].y << ", " << triangle.vertices[0].z << " to " << transformedTriangle.vertices[0].x << ", " << transformedTriangle.vertices[0].y << ", " << transformedTriangle.vertices[0].z << std::endl;

//      clock_t start, end;
//      start = clock();
//      bool result;
//      for (int count = 0; count < maxCount; count++) {
//        result = circle.checkTriangleIntersection(transformedTriangle);
//      }
//      end = clock();
//      double totalTime = (double)(end-start)/CLOCKS_PER_SEC;
//      std::cout << "Result: " << result << std::endl;
//      std::cout << "Time: " << totalTime/maxCount << ", total: " << totalTime << " seconds." << std::endl;
//    }



//    glm::vec2 point = glm::vec2(2.0f, 2.0f);
//    glm::vec2 direction = glm::vec2(1.0f, 1.0f);
//    glm::vec2 closestPoint = ZCircle(0.5f).closestPointToCenterOnLine(point, direction);

//    std::cout << closestPoint.x << ", " << closestPoint.y << std::endl;
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
