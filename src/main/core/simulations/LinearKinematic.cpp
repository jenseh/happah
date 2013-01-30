#include "LinearKinematic.h"

LinearKinematic::LinearKinematic(int iterations, glm::vec3 start, glm::vec3 end):Kinematic(iterations)
{
    m_CurrentMatrix = glm::translate(glm::mat4(1.0f), start);
    m_Delta = end - start;
    m_Delta /= (float)iterations;
}

void LinearKinematic::calcNextMatrix(){
    m_CurrentMatrix = glm::translate(m_CurrentMatrix, m_Delta);
    Kinematic::calcNextMatrix();
}

