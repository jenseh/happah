#include "CircleTriangleIntersectionTest.h"
#include <cstdlib>

float getRand() {
  return (float)rand()/(float)RAND_MAX;
}

CircleTriangleIntersectionTest::CircleTriangleIntersectionTest() {
    InvoluteGear* gear1 = new InvoluteGear();
    InvoluteGear* gear2 = new InvoluteGear();

    // Test cases
    Circle circle0 = Circle(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), 1.0f);
    Circle circle1 = Circle(glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f), 1.0f);
    Circle circle2 = Circle(glm::vec3(0.0f, 0.0f, 0.026f), glm::vec3(0.0f, 0.0f, 1.0f), 1.10031f);
    Circle circle3 = Circle(glm::vec3(0.0f, 0.0f, 0.021f), glm::vec3(0.0f, 0.0f, 1.0f), 2.0f);//remove

    std::vector<Circle*> circles;

    circles.push_back(&circle0);
    circles.push_back(&circle1);
    circles.push_back(&circle2);
    circles.push_back(&circle3);




    {
      std::cout << "Running Circle tests:" << std::endl;
      bool totalResult = true;

      std::list<CircleHitResult*>* hitResults = new std::list<CircleHitResult*>;
      for (unsigned int c = 0; c < circles.size(); c++) {
          Circle* circle = circles[c];

          // Triangle with same center point
          Triangle triangle0 = Triangle(circle->m_center,
                                        glm::vec3(getRand(), getRand(), getRand()),
                                        glm::vec3(getRand(), getRand(), getRand()));

          // Triangle that is included in circle
          Triangle triangle1 = Triangle(circle->m_center + glm::vec3(circle->m_radius / 2.0f, 0.0f, 0.0f),
                                        circle->m_center + glm::vec3(0.0f, circle->m_radius / 2.0f, 0.0f),
                                        circle->m_center);

          // Triangle that intersects circle in at least one edge point
          Triangle triangle2 = Triangle(circle->m_center + glm::vec3(circle->m_radius, 0.0f, 0.0f),
                                        glm::vec3(getRand(), getRand(), getRand()),
                                        glm::vec3(getRand(), getRand(), getRand()));

          // Triangle that is in the same plane but too far away
          Triangle triangle3 = Triangle(circle->m_center + glm::vec3(circle->m_radius, circle->m_radius, 0.0f),
                                        circle->m_center + glm::vec3(circle->m_radius * 2.0f, circle->m_radius * 3.0f, 0.0f),
                                        circle->m_center + glm::vec3(circle->m_radius * 8.0f, circle->m_radius * 10.0f, 0.0f));

          // Triangle that is parallel to circle
          Triangle triangle4 = Triangle(circle->m_center + glm::vec3(0.0f, 0.0f, 1.0f),
                                        circle->m_center + glm::vec3(circle->m_radius, 0.0f, 1.0f),
                                        circle->m_center + glm::vec3(0.0f, circle->m_radius, 1.0f));

          // Triangle that cuts through the circle plane
          Triangle triangle5 = Triangle(circle->m_center + glm::vec3(0.0f, 0.0f, -1.0f),
                                        circle->m_center + glm::vec3(0.0f, 0.0f, 1.0f),
                                        circle->m_center + glm::vec3(0.0f, 1.0f, 1.0f));

          // Circle that is included in triangle
          Triangle triangle6 = Triangle(circle->m_center + glm::vec3(circle->m_radius * 10.0f, 0.0f, 0.0f),
                                        circle->m_center + glm::vec3(0.0f, circle->m_radius * 10.0f, 0.0f),
                                        circle->m_center + glm::vec3(circle->m_radius * -10.0f, circle->m_radius * -10.0f, 0.0f));


          std::vector<Triangle*> triangles;
          triangles.push_back(&triangle0);
          triangles.push_back(&triangle1);
          triangles.push_back(&triangle2);
          triangles.push_back(&triangle3);
          triangles.push_back(&triangle4);
          triangles.push_back(&triangle5);
          triangles.push_back(&triangle6);

          // Define the vector that holds the results
          bool results[7] = {1, 1, 1, 0, 0, 1, 1};

          for (unsigned int t = 0; t < triangles.size(); t++) {
              bool result = circle->intersect(triangles[t], hitResults);
              bool matchesSolution = (result == results[t]);
              std::cout << "Result: [" << c << ", " << t << "]: " << result << " -> " << matchesSolution << std::endl;
              if (!matchesSolution) totalResult = false;
            }
        }
      if (totalResult) {
          std::cout << "Success: All tests finished successfully!" << std::endl;
      } else {
          std::cout << "Error: At least one test failed!" << std::endl;
      }

    }
}
