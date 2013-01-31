#include "Picker.h"
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>


using namespace std;
Picker::Picker()
{

}

bool Picker::select(float x, float y, float width, float height, glm::mat4 *toWorld){
  cout <<"Mouseposition = " << x << "/" << y << endl;

  // Create Normalized Device Coordinates
        float ndc_x = (x-(width/2.0f))/(width/2.0f);
        float ndc_y = -(y-(height/2.0f))/(height/2.0f);
        float ndc_z = 0.0f;

        cout << "NDC's are "<< ndc_x << "/" << ndc_y << endl;

  // Create Ray
        glm::vec4 rayPos = glm::vec4(ndc_x,ndc_y,ndc_z,1.0f);
        glm::vec4 rayDir = glm::vec4(0.0f,0.0f,1.0f,1.0f);
        cout << "Ray Position :" << rayPos.x << "/" << rayPos.y<< "/" << rayPos.z << endl;
        cout << "Ray Direction :" << rayDir.x << "/" << rayDir.y<< "/" << rayDir.z << endl;

        // Transform Ray into World Position

        rayPos = *toWorld * rayPos;
        rayDir = *toWorld * rayDir;
        cout << "Ray World Position :" << rayPos.x << "/" << rayPos.y<< "/" << rayPos.z << endl;
        cout << "Ray World Direction :" << rayDir.x << "/" << rayDir.y<< "/" << rayDir.z << endl;
        return true;
}
