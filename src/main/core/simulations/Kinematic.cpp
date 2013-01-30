#include "Kinematic.h"

Kinematic::Kinematic(int iterations)
{
    m_Iterations = iterations;
    m_CurrentInteration = 0;
}

bool Kinematic::done(){
    return m_CurrentInteration > m_Iterations;
}

glm::mat4 Kinematic::getCurrentMatrix(){
    return m_CurrentMatrix;
}

void Kinematic::calcNextMatrix(){
    m_CurrentInteration++;
}
