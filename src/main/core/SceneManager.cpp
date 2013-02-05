#include "SceneManager.h"
#include <time.h>
#include "../test/WormGearGrindTest.h"
#include "../test/KinematicTest.h"
#include "geometries/Sphere.h"
#include "geometries/TriPatch.h"
#include <iostream>


SceneManager::SceneManager() : m_iDCounter(0) {
    std::cout << " SM: size" << m_drawables.size()<< std::endl;
 //   new WormGearGrindTest();
    //KinematicTest test;
    //test.runLinearTest();
}

SceneManager::~SceneManager() {
}

//first idDrawable gets id 0, m_idCounter is has number of produced idDrawables
uint SceneManager::addDrawable(Drawable *drawable) {
    IdDrawable  idDrawable = {m_iDCounter, drawable};
    m_drawables.push_back(idDrawable);
    m_iDCounter += 1;
    return idDrawable.id;
}

void SceneManager::removeDrawable(uint id) {
    std::list<IdDrawable>::iterator candidate = m_drawables.end();
    for(std::list<IdDrawable>::iterator it = m_drawables.begin(), eend = m_drawables.end(); it != eend; ++it) {
        if (it->id == id) {
            candidate = it;
        }
    }
    if(candidate != m_drawables.end()){
        m_drawables.erase(candidate);
        m_deletedCounter += 1;
    }
}

vector<Drawable*>* SceneManager::getDrawables() {
    std::vector<Drawable*> *drawables = new std::vector<Drawable*>;

    for(std::list<IdDrawable>::iterator it = m_drawables.begin(); it != m_drawables.end(); ++it) {
        drawables->push_back(it->drawable);
    }
    return drawables;
}

unsigned int SceneManager::getObjectState() {
    return m_iDCounter + m_deletedCounter;
}

void SceneManager::buildScene(){
  Sphere * sphere = new Sphere(1.0f,glm::vec4(2.0f,0.0f,0.0f,1.0f));
  QuadMesh* dSphere = sphere->toQuadMesh();
  dSphere->setMaterial(0.45f,        //ka
                       0.5f,        //kd
                       1.0f,        //ks
                       10.0f);      //phong
  std::vector<Color>* colorData = new std::vector<Color>();
  for(uint i = 0; i < (dSphere->getVertexData()->size()/2); i++){
    Color color;
    color.red =1.0f;
    color.green = 0.0f;
    color.blue = 0.0f;
    color.alpha = 1.0f;
    colorData->push_back(color);
  }
  dSphere->setColorData(*colorData);
  std::cout << "VertexData size :" << dSphere->getVertexData()->size() << endl;
  std::cout << " Color Data size :" << colorData->size() << endl;
//  uint result = addDrawable(dSphere);

  TriPatch* tripatch = new TriPatch(2,glm::vec3(0.0f),glm::vec3(0.0f,2.0f,0.0f),glm::vec3(0.0f,2.0f,1.0f), "patch");
  tripatch->setControlPoint(2,glm::vec3(1.0f,0.0f,2.0f));
  tripatch->setControlPoint(4,glm::vec3(0.0f,1.0f,0.0f));
  tripatch->setControlPoint(1,glm::vec3(1.0f,1.0f,1.0f));
  tripatch->update();

  TriPatch* tripatch2 = new TriPatch(2,glm::vec3(0.0f),glm::vec3(0.0f,0.0f,-1.0f),glm::vec3(0.0f,2.0f,0.0f), "patch2");
  tripatch2->setControlPoint(2,glm::vec3(1.0f,1.0f,1.0f));
  tripatch2->update();

  TriPatch* tripatch3 =  new TriPatch(2,glm::vec3(0.0f),glm::vec3(0.0f,2.0f,1.0f),glm::vec3(-2.0f,1.0f,0.0f), "patch3");
  tripatch3->setControlPoint(1,glm::vec3(1.0f,0.0f,2.0f));
  tripatch3->update();

  TriangleMesh* dTriPatch = tripatch->toTriangleMesh();
  TriangleMesh* dTriPatch2 = tripatch2->toTriangleMesh();
  TriangleMesh* dTriPatch3 = tripatch3->toTriangleMesh();

//  result = addDrawable(dTriPatch);
//  result = addDrawable(dTriPatch2);
//  result = addDrawable(dTriPatch3);
}
