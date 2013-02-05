#include "KinematicTest.h"

KinematicTest::KinematicTest()
{
}



void KinematicTest::runLinearTest(){
    glm::vec4 point(0,0,0,1);
    Kinematic linKin = Kinematic::getLinearKinematic(glm::vec3(-1,-1.5,-1), glm::vec3(5,5,5));
    for( double t = 0; t < 1; t += 0.1){
        glm::mat4 matrix = linKin.getMatrix(t);
        glm::vec4 curPoint = matrix * point;
        std::cout<<"t:"<<t<<"  "<<curPoint.x<<" "<<curPoint.y<<" "<<curPoint.z<<endl;
    }
}
