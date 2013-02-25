#include <ctime>
#include <iostream>

#include "happah/geometries/ControlNet2.h"
#include "happah/geometries/Sphere.h"
#include "happah/geometries/SpherePatch.h"
#include "happah/geometries/TriPatch.h"
#include "happah/scene/SceneManager.h"

SceneManager::SceneManager() : m_iDCounter(0) {
//    new WormGearGrindTest(this);
//    buildScene();
    //KinematicTest test;
    //test.runLinearTest();
   m_iDNCounter = 0;
}

SceneManager::~SceneManager() {
}

//first idDrawable gets id 0, m_idCounter is has number of produced idDrawables
uint SceneManager::addDrawable(Drawable *drawable) {
    IdDrawable idDrawable = {m_iDCounter, drawable};
    m_drawables.push_back(idDrawable);
    m_iDCounter += 1;
    notifyListeners();
    return idDrawable.id;
}

void SceneManager::removeDrawable(uint id) {
    std::list<IdDrawable>::iterator candidate = m_drawables.end();
    for(std::list<IdDrawable>::iterator it = m_drawables.begin(), end = m_drawables.end(); it != end; ++it) {
        if (it->id == id) {
            candidate = it;
        }
    }
    if(candidate != m_drawables.end()){
        m_drawables.erase(candidate);
        notifyListeners();
    }
}

vector<Drawable*>* SceneManager::getDrawables() {
    std::vector<Drawable*> *drawables = new std::vector<Drawable*>;

    for(std::list<IdDrawable>::iterator it = m_drawables.begin(); it != m_drawables.end(); ++it) {
        drawables->push_back(it->drawable);
    }
    return drawables;
}

void SceneManager::buildScene(){
  Sphere* sphere = new Sphere(1.0f, glm::vec4(0.0f,0.0f,0.0f,1.0f));
  QuadMesh* dSphere = sphere->toQuadMesh();
  dSphere->setMaterial(1.0f,        //ka
                       1.5f,        //kd
                       1.8f,        //ks
                       5.0f);      //phong
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
  uint result = addDrawable(dSphere);
/*
  TriPatch* tripatch = new TriPatch(2,glm::vec3(0.0f,0.0f,1.0f),glm::vec3(1.0f,0.0f,0.0f),glm::vec3(0.0f,1.0f,0.0f), "patch");
  addNonDrawable(tripatch);
  tripatch->setControlPoint(0,(tripatch->getControlPoint(0))*1.3f);
  tripatch->setControlPoint(4,(tripatch->getControlPoint(4))*1.8f);

  tripatch->update();
  ControlNet2* cnet = new ControlNet2(tripatch->getControlPoint(0),
                                     tripatch->getControlPoint(1),
                                     tripatch->getControlPoint(2),
                                     tripatch->getControlPoint(3),
                                     tripatch->getControlPoint(4),
                                     tripatch->getControlPoint(5),"cnet");

  TriPatch* tripatch2 = new TriPatch(2,glm::vec3(1.0f,0.0f,0.0f),glm::vec3(0.0f,0.0f,-1.0f),glm::vec3(0.0f,1.0f,0.0f), "patch2");
 addNonDrawable(tripatch2);
  tripatch2->setControlPoint(2,(tripatch2->getControlPoint(2))*1.8f);
 tripatch2->update();
 ControlNet2* cnet2 = new ControlNet2(tripatch2->getControlPoint(0),
                                    tripatch2->getControlPoint(1),
                                    tripatch2->getControlPoint(2),
                                    tripatch2->getControlPoint(3),
                                    tripatch2->getControlPoint(4),
                                    tripatch2->getControlPoint(5),"cnet2");
  TriPatch* tripatch3 =  new TriPatch(2,glm::vec3(0.0f,0.0f,-1.0f),glm::vec3(-1.0f,0.0f,0.0f),glm::vec3(0.0f,1.0f,0.0f), "patch3");
  addNonDrawable(tripatch3);
//  tripatch3->setControlPoint(1,glm::vec3(1.0f,0.0f,2.0f));
//  tripatch3->update();
  ControlNet2* cnet3 = new ControlNet2(tripatch3->getControlPoint(0),
                                     tripatch3->getControlPoint(1),
                                     tripatch3->getControlPoint(2),
                                     tripatch3->getControlPoint(3),
                                     tripatch3->getControlPoint(4),
                                     tripatch3->getControlPoint(5),"cnet3");
 TriPatch* tripatch4 =  new TriPatch(2,glm::vec3(-1.0f,0.0f,0.0f),glm::vec3(0.0f,0.0f,1.0f),glm::vec3(0.0f,1.0f,0.0f), "patch4");
addNonDrawable(tripatch4);
ControlNet2* cnet4 = new ControlNet2(tripatch4->getControlPoint(0),
                                   tripatch4->getControlPoint(1),
                                   tripatch4->getControlPoint(2),
                                   tripatch4->getControlPoint(3),
                                   tripatch4->getControlPoint(4),
                                   tripatch4->getControlPoint(5),"cnet4");

  TriangleMesh* dTriPatch = tripatch->toTriangleMesh();
  dTriPatch->setColor(1.0f,1.0f,1.0f,1.0f);
  dTriPatch->setMaterial(1.3f,1.0f,1.5f,20.0f);
  TriangleMesh* dTriPatch2 = tripatch2->toTriangleMesh();
  dTriPatch2->setColor(1.0f,1.0f,1.0f,1.0f);
  dTriPatch2->setMaterial(1.3f,1.0f,1.5f,20.0f);
  TriangleMesh* dTriPatch3 = tripatch3->toTriangleMesh();
  dTriPatch3->setColor(1.0f,1.0f,1.0f,1.0f);
  dTriPatch3->setMaterial(1.3f,1.0f,1.5f,20.0f);
  TriangleMesh* dTriPatch4 = tripatch4->toTriangleMesh();
  dTriPatch4->setColor(1.0f,1.0f,1.0f,1.0f);
  dTriPatch4->setMaterial(1.3f,1.0f,1.5f,20.0f);
  TriangleMesh* dcnet = cnet->toTriangleMesh();
  dcnet->setColor(1.0f,0.0f,0.0f,1.0f);
  TriangleMesh* dcnet2 = cnet2->toTriangleMesh();
  dcnet2->setColor(1.0f,0.0f,0.0f,1.0f);
  TriangleMesh* dcnet3 = cnet3->toTriangleMesh();
  dcnet3->setColor(1.0f,0.0f,0.0f,1.0f);
  TriangleMesh* dcnet4 = cnet4->toTriangleMesh();
  dcnet4->setColor(1.0f,0.0f,0.0f,1.0f);
  int result;
  result = addDrawable(dTriPatch);
  result = addDrawable(dTriPatch2);
  result = addDrawable(dTriPatch3);
  result = addDrawable(dTriPatch4);
  result = addDrawable(dcnet);
  result = addDrawable(dcnet2);
  result = addDrawable(dcnet3);
  result = addDrawable(dcnet4);

  SpherePatch* spherePatch = new SpherePatch(2,glm::vec3(0.0f,0.0f,1.5f),glm::vec3(1.5f,0.0f,0.0f),glm::vec3(0.0f,1.5f,0.0f),"SpherePatch");
  TriangleMesh* dSpherePatch = spherePatch->toTriangleMesh();
  dSpherePatch->setColor(1.0f,1.0f,1.0f,1.0f);

  SpherePatch* spherePatch1 = new SpherePatch(2,glm::vec3(1.5f,0.0f,0.0f),glm::vec3(0.0f,0.0f,-1.5f),glm::vec3(0.0f,1.5f,0.0f),"SpherePatch1");
  TriangleMesh* dSpherePatch1 = spherePatch1->toTriangleMesh();
  dSpherePatch1->setColor(1.0f,0.0f,0.0f,1.0f);

  SpherePatch* spherePatch2 = new SpherePatch(2,glm::vec3(0.0f,0.0f,-1.5f),glm::vec3(-1.5f,0.0f,0.0f),glm::vec3(0.0f,1.5f,0.0f),"SpherePatch2");
  TriangleMesh* dSpherePatch2 = spherePatch2->toTriangleMesh();
  dSpherePatch2->setColor(0.0f,1.0f,0.0f,1.0f);

  SpherePatch* spherePatch3 = new SpherePatch(2,glm::vec3(-1.5f,0.0f,0.0f),glm::vec3(0.0f,0.0f,1.5f),glm::vec3(0.0f,1.5f,0.0f),"SpherePatch3");
  TriangleMesh* dSpherePatch3 = spherePatch3->toTriangleMesh();
  dSpherePatch3->setColor(0.0f,0.0f,1.0f,1.0f);



  int result;

  result = addDrawable(dSpherePatch);
  result = addDrawable(dSpherePatch1);
  result = addDrawable(dSpherePatch2);
  result = addDrawable(dSpherePatch3);
  */
}


void SceneManager::addNonDrawable(NonDrawable *nonDrawable){
  IdNonDrawable idNonDrawable = {m_iDNCounter, nonDrawable};
  m_nonDrawables.push_back(idNonDrawable);
  m_iDNCounter += 1;
}

std::vector<NonDrawable*>* SceneManager::getNonDrawables(){
  std::vector<NonDrawable*> *nonDrawables = new std::vector<NonDrawable*>;

  for(std::list<IdNonDrawable>::iterator it = m_nonDrawables.begin(); it != m_nonDrawables.end(); ++it) {
      nonDrawables->push_back(it->nonDrawable);
  }
  return nonDrawables;
}

void SceneManager::drawablesChanged() {
    notifyListeners();
  }

void SceneManager::registerListener(SceneListener* sceneListener) {
    m_listeners.push_back(sceneListener);
  }

void SceneManager::notifyListeners() {
  for(std::list<SceneListener*>::iterator it = m_listeners.begin(), end = m_listeners.end();
    it != end; ++it) {
    (*it)->sceneChanged();
  }
}