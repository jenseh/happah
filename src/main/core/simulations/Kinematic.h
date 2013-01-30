#ifndef KINEMATIC_H
#define KINEMATIC_H
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Kinematic
{
    int m_Iterations;
    int m_CurrentInteration;
protected:
    glm::mat4 m_CurrentMatrix;

public:
  Kinematic(int iterations);

  bool done();
  glm::mat4 getCurrentMatrix();
  virtual void calcNextMatrix(); // needs to be implemented by specific kinematic
};

#endif // KINEMATIC_H
