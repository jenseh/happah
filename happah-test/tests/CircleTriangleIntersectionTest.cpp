#include "CircleTriangleIntersectionTest.h"
#include <cstdlib>
#include "happah/LoggingUtils.h"

float getRand() {
  return (float)rand()/(float)RAND_MAX;
}

CircleTriangleIntersectionTest::CircleTriangleIntersectionTest() {
    InvoluteGear* gear1 = new InvoluteGear();
    InvoluteGear* gear2 = new InvoluteGear();

    // Test cases
    Circle circle0 = Circle(hpvec3(0.0, 0.0, 0.0),   hpvec3(0.0, 0.0, 1.0), 1.0);
    Circle circle1 = Circle(hpvec3(0.0, 0.0, 1.0),   hpvec3(0.0, 0.0, 1.0), 1.0);
    Circle circle2 = Circle(hpvec3(0.0, 0.0, 0.026), hpvec3(0.0, 0.0, 1.0), 1.10031);
    Circle circle3 = Circle(hpvec3(0.0, 0.0, 0.021), hpvec3(0.0, 0.0, 1.0), 2.0);//remove

    std::vector<Circle*> circles;

    circles.push_back(&circle0);
    circles.push_back(&circle1);
    circles.push_back(&circle2);
    circles.push_back(&circle3);




    {
      std::cout << "Running Circle tests:" << std::endl;
      bool totalResult = true;

      std::list<CircleHitResult>* hitResults = new std::list<CircleHitResult>;
      for (unsigned int c = 0; c < circles.size(); c++) {
          Circle* circle = circles[c];

          // Triangle with same center point
          Triangle triangle0 = Triangle(circle->m_center,
                                        hpvec3(getRand(), getRand(), getRand()),
                                        hpvec3(getRand(), getRand(), getRand()));

          // Triangle that is included in circle
          Triangle triangle1 = Triangle(circle->m_center + hpvec3(circle->m_radius / 2.0, 0.0, 0.0),
                                        circle->m_center + hpvec3(0.0, circle->m_radius / 2.0, 0.0),
                                        circle->m_center);

          // Triangle that intersects circle in at least one edge point
          hpvec3 orthogonalToNormal = glm::normalize(glm::cross(circle->m_normal, circle->m_normal + hpvec3(1.0, 0.0, 0.0)));
          Triangle triangle2 = Triangle(circle->m_center + orthogonalToNormal * circle->m_radius,
  	  	  	  	  						hpvec3(1.0, 1.0, 3.0),
  	  	  	  	  						hpvec3(-1.0, 2.0, 1.0));
//        		  	  	  	  	  	  	hpvec3(getRand(), getRand(), getRand()),
//        		                        hpvec3(getRand(), getRand(), getRand()));
//        		  	  	  	  	  	  	circle->m_center + hpvec3(2.0 * circle->m_radius, -1.0, 0.0),
//        		  	  	  	  	  	    circle->m_center + hpvec3(2.0 * circle->m_radius, 1.0, 0.0));

          // Triangle that is in the same plane but too far away
          Triangle triangle3 = Triangle(circle->m_center + hpvec3(circle->m_radius, circle->m_radius, 0.0),
                                        circle->m_center + hpvec3(circle->m_radius * 2.0, circle->m_radius * 3.0, 0.0),
                                        circle->m_center + hpvec3(circle->m_radius * 8.0, circle->m_radius * 10.0, 0.0));

          // Triangle that is parallel to circle
          Triangle triangle4 = Triangle(circle->m_center + hpvec3(0.0, 0.0, 1.0),
                                        circle->m_center + hpvec3(circle->m_radius, 0.0, 1.0),
                                        circle->m_center + hpvec3(0.0, circle->m_radius, 1.0));

          // Triangle that cuts through the circle plane
          Triangle triangle5 = Triangle(circle->m_center + hpvec3(0.0, 0.0, -1.0),
                                        circle->m_center + hpvec3(0.0, 0.0, 1.0),
                                        circle->m_center + hpvec3(0.0, 1.0, 1.0));

          // Circle that is included in triangle
          Triangle triangle6 = Triangle(circle->m_center + hpvec3(circle->m_radius * 10.0, 0.0, 0.0),
                                        circle->m_center + hpvec3(0.0, circle->m_radius * 10.0, 0.0),
                                        circle->m_center + hpvec3(circle->m_radius * -10.0, circle->m_radius * -10.0, 0.0));


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

              if (t == 2 && !matchesSolution) {
            	  Triangle triangle = *(triangles[t]);
            	  LoggingUtils::print("Triangle2", triangle);
              }

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
