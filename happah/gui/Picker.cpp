#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <QMatrix4x4>

#include "happah/geometries/NonDrawable.h"
#include "happah/gui/Picker.h"
#include "happah/models/Drawable.h"

using namespace std;
Picker::Picker()
{

}

bool Picker::select(float x, float y, float width, float height, glm::mat4 *toWorld,SceneManager* sceneManager){
  cout <<"Mouseposition = " << x << "/" << y << endl;

  // Create Normalized Device Coordinates
        float ndc_x = (x-(width/2.0f))/(width/2.0f);
        float ndc_y = -(y-(height/2.0f))/(height/2.0f);
        float ndc_z = 0.0f;

        cout << "NDC's are "<< ndc_x << "/" << ndc_y << endl;
  /*
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
     */

       // Quick And very DIRTY
      std::vector<NonDrawable*>* nonDrawables = sceneManager->getNonDrawables();

        for (int i=0; i < nonDrawables->size();i++){
            NonDrawable* testNonDrawable = nonDrawables->at(i);
            cout << "Drawable Name: "<< testNonDrawable->getName()<< endl;
            for (int j=0;j< 6;j++){
                glm::vec4 cp = glm::vec4(testNonDrawable->getControlPoint(i),1.0f);

                cp = *toWorld*cp;
                float bias = 0.01;
                cout << "NDC "<< ndc_x << "/" << ndc_y << endl;
                cout << "CP  "<< cp.x << "/"<<cp.y << endl;
                //if (ndc_x < cp.x+bias && ndc_x > cp.x-bias){
                //if((ndc_x > cp.x-bias) && (ndc_x < cp.x-bias) && (ndc_y > cp.y-bias) && (ndc_y < cp.y+bias)){
                //    cout << "Picker fetched Controlpoint: " << j << endl;
                //    cout << "of Patch: " <<testNonDrawable->getName()<<endl;
                //  }
            }
        }
        return true;
}
