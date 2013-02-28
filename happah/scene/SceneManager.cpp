#include <ctime>
#include <iostream>

#include "happah/geometries/ControlNet2.h"
#include "happah/geometries/Sphere.h"
#include "happah/geometries/SpherePatch.h"
#include "happah/geometries/TriPatch.h"
#include "happah/scene/InvoluteSpurGearNode.h"
#include "happah/scene/SceneManager.h"

SceneManager::SceneManager() : m_iDCounter(0) {
//    new WormGearGrindTest(this);
//    buildScene();
    //KinematicTest test;
    //test.runLinearTest();
   m_iDNCounter = 0;
}

SceneManager::~SceneManager() {}

//TODO: change to TriangleMesh_ptr
void SceneManager::add(InvoluteSpurGear_ptr involuteSpurGear, TriangleMesh* triangleMesh) {
	InvoluteSpurGearNode_ptr involuteSpurGearNodePtr(new InvoluteSpurGearNode(involuteSpurGear));
	addChild(involuteSpurGearNodePtr);

	TriangleMesh_ptr triangleMeshPtr(triangleMesh);
	TriangleMeshNode_ptr triangleMeshNodePtr(new TriangleMeshNode(triangleMeshPtr));
	involuteSpurGearNodePtr->addChild(triangleMeshNodePtr);

	notifyListeners();
}

void SceneManager::visit(InvoluteSpurGearNode& involuteSpurGearNode) {}

void SceneManager::visit(TriangleMeshNode& triangleMeshNode) {
	m_vectorDrawables->push_back(triangleMeshNode.getGeometry().get());
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
	m_vectorDrawables = new vector<Drawable*>();

	accept(*this);
	
	return m_vectorDrawables;

	/*vector<Drawable*>* drawables = new vector<Drawable*>();
	for(std::list<IdDrawable>::iterator it = m_drawables.begin(); it != m_drawables.end(); ++it) {
        drawables->push_back(it->drawable);
    }
    return drawables;*/
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
