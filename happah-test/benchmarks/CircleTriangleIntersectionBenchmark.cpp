#include "CircleTriangleIntersectionBenchmark.h"

CircleTriangleIntersectionBenchmark::CircleTriangleIntersectionBenchmark() {
  InvoluteGear* gear1 = new InvoluteGear();//gears of radius 1 with 20 teeth are ~1.5 units away
  InvoluteGear* gear2 = new InvoluteGear();

  // Test cases
  int maxCount = 1;
  Triangle triangle = Triangle(glm::vec3(-0.154736f, -0.886598f, 0.00f),
                               glm::vec3(-0.161695f,  -0.885356f, 0.075f),
                               glm::vec3(-0.154736f, -0.886598f, 0.075f));

  {
    std::cout << "Running Circle benchmark:" << std::endl;
    Circle circle = Circle(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), 1.0f);

    clock_t start, end;
    start = clock();
    bool result;
    std::list<CircleHitResult*>* hitResults = new std::list<CircleHitResult*>;
    for (int count = 0; count < maxCount; count++) {
        result = circle.intersect(&triangle, hitResults);
      }
    end = clock();
    double totalTime = (double)(end-start)/CLOCKS_PER_SEC;
    std::cout << "Result: " << result << std::endl;
    std::cout << "Time: " << totalTime/maxCount << ", total: " << totalTime << " seconds." << std::endl;
  }
}
