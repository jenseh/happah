#include <ctime>
#include <iostream>

#include "happah/scene/SceneManager.h"

SceneManager::SceneManager() {}

SceneManager::~SceneManager() {}

void SceneManager::add(InvoluteGear_ptr involuteGear, TriangleMesh_ptr triangleMesh, hpcolor& color) {
	Node_ptr node = find(involuteGear);

	InvoluteGearNode_ptr involuteGearNode;
	if(node) {
		involuteGearNode = dynamic_pointer_cast<InvoluteGearNode>(node);
		node = involuteGearNode->find(triangleMesh);
		if(node) {
			TriangleMeshNode_ptr triangleMeshNode = dynamic_pointer_cast<TriangleMeshNode>(node);
			TriangleMeshRenderStateNode_ptr triangleMeshRenderStateNode = triangleMeshNode->getTriangleMeshRenderStateNode();
			triangleMeshRenderStateNode->setColor(color);
			return;
		}
	} else {
		involuteGearNode = InvoluteGearNode_ptr(new InvoluteGearNode(involuteGear));
		addChild(involuteGearNode);
	}

	TriangleMeshNode_ptr triangleMeshNode(new TriangleMeshNode(triangleMesh));
	involuteGearNode->addChild(triangleMeshNode);

	TriangleMeshRenderStateNode_ptr triangleMeshRenderStateNode(new TriangleMeshRenderStateNode(triangleMesh, color));
	triangleMeshNode->addChild(triangleMeshRenderStateNode);

	notifyListeners();
}

void SceneManager::remove(InvoluteGear_ptr involuteGear, TriangleMesh_ptr triangleMesh) {
	Node_ptr node = find(involuteGear);

	if(node) {
		InvoluteGearNode_ptr involuteGearNode = dynamic_pointer_cast<InvoluteGearNode>(node);
		node = involuteGearNode->find(triangleMesh);
		if(node)
			involuteGearNode->removeChild(dynamic_pointer_cast<TriangleMeshNode>(node));
	}

	notifyListeners();
}

void SceneManager::visit(InvoluteGearNode& involuteGearNode) {}

void SceneManager::visit(TriangleMeshNode& triangleMeshNode) {
	m_vectorDrawables->push_back(triangleMeshNode.getGeometry().get());
}

void SceneManager::visit(TriangleMeshRenderStateNode& triangleMeshRenderStateNode) {}

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
