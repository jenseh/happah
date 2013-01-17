#include "CircleTriangleIntersectionBenchmark.h"

CircleTriangleIntersectionBenchmark::CircleTriangleIntersectionBenchmark() {
  // Test cases
    int maxCount = 1;
    Triangle triangle = Triangle(glm::vec3(-0.154736f, -0.886598f, 0.05f),
                                 glm::vec3(-0.161695f,  -0.885356f, 0.075f),
                                 glm::vec3(-0.154736f, -0.886598f, 0.075f));

    {
      std::cout << "Running Circle benchmark:" << std::endl;
      Circle circle = Circle(glm::vec3(-5.0f, 0.0f, 0.05f), glm::vec3(0.0f, 0.0f, 1.0f), 1.0f);
//      Triangle transformedTriangle = WormGearGrind(*gear1, *gear2).transformTriangle(triangle);
//      std::cout << "Transformation-A: " << triangle.vertices[0].x << ", " << triangle.vertices[0].y << ", " << triangle.vertices[0].z << " to " << transformedTriangle.vertices[0].x << ", " << transformedTriangle.vertices[0].y << ", " << transformedTriangle.vertices[0].z << std::endl;

      clock_t start, end;
      start = clock();
      bool result;
      CircleHitResult* hitResult;
      for (int count = 0; count < maxCount; count++) {
        result = circle.intersect(triangle, hitResult);
      }
      end = clock();
      double totalTime = (double)(end-start)/CLOCKS_PER_SEC;
      std::cout << "Result: " << result << std::endl;
      std::cout << "Time: " << totalTime/maxCount << ", total: " << totalTime << " seconds." << std::endl;
    }
}
