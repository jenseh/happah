#include "KinematicTest.h"

KinematicTest::KinematicTest()
{
}


void KinematicTest::runLinearTest(){
    LinearKinematic test1(20,glm::vec3(-5,-5,5), glm::vec3(5,5,-5));
    glm::vec4 point;
    while(!test1.done() ){
        point = test1.getCurrentMatrix() * glm::vec4(-1,1,1,1);
        std::cout<<point.x <<" "<<point.y<<" "<<point.z<<std::endl;
        test1.calcNextMatrix();
    }
}
