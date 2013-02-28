#include <ctime>
#include <iostream>

#include "happah/scene/SceneManager.h"

SceneManager::SceneManager() : m_iDCounter(0) {
   m_iDNCounter = 0;
}

SceneManager::~SceneManager() {}

void SceneManager::add(InvoluteGear_ptr involuteGear, TriangleMesh_ptr triangleMesh) {
	Node_ptr nodePtr = find(involuteGear);

	InvoluteGearNode_ptr involuteGearNodePtr;
	if(nodePtr)
		involuteGearNodePtr = dynamic_pointer_cast<InvoluteGearNode>(nodePtr);
	else {
		involuteGearNodePtr = InvoluteGearNode_ptr(new InvoluteGearNode(involuteGear));
		addChild(involuteGearNodePtr);
	}

	TriangleMeshNode_ptr triangleMeshNodePtr(new TriangleMeshNode(triangleMesh));
	involuteGearNodePtr->addChild(triangleMeshNodePtr);

	notifyListeners();
}

void SceneManager::remove(InvoluteGear_ptr involuteGear, TriangleMesh_ptr triangleMesh) {
	Node_ptr nodePtr = find(involuteGear);

	if(nodePtr) {
		InvoluteGearNode_ptr involuteGearNodePtr = dynamic_pointer_cast<InvoluteGearNode>(nodePtr);
	}
}

void SceneManager::visit(InvoluteGearNode& involuteGearNode) {}

void SceneManager::visit(TriangleMeshNode& triangleMeshNode) {
	m_vectorDrawables->push_back(triangleMeshNode.getGeometry().get());
}
void SceneManager::visit(TriangleMeshRenderStateNode& triangleMeshRenderStateNode){

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
