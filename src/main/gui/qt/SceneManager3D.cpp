#include "SceneManager3D.h"

#include <iostream>

SceneManager3D::SceneManager3D(SceneManager* sceneManager, ComponentList* list)
		: m_sceneManager(sceneManager), m_componentList(list)
{
	connect(m_componentList, SIGNAL(selectionChanged(unsigned int)), this, SLOT(selectByListID(unsigned int)));
}

void SceneManager3D::addDrawable(RenderItem3D* renderItem) {
	ManagedItem item;
	item.renderItem = renderItem;
	item.sceneID = m_sceneManager->addDrawable(renderItem->getDrawable());
	item.listID = m_componentList->addNewItem(renderItem->getName());
	m_componentList->selectItem(item.listID);
	for(std::list<ManagedItem>::iterator it = m_drawables.begin();
				it != m_drawables.end();
				++it )
	{
		it->active=false;
	}
	item.active = true;

	m_drawables.push_back(item);
}

void SceneManager3D::selectByListID(unsigned int itemID) {
	for(std::list<ManagedItem>::iterator it = m_drawables.begin();
				it != m_drawables.end();
				++it )
	{
		it->active = it->listID == itemID;
		if (it->active) {
			emit updateTool(it->renderItem);
		}
	}
}

void SceneManager3D::deleteCurrentDrawable(std::string name) {
	std::list<ManagedItem>::iterator candidate = m_drawables.end();
	for(std::list<ManagedItem>::iterator it = m_drawables.begin();
				it != m_drawables.end();
				++it)
	{
		if(it->active && it->renderItem->getName() == name) {
			candidate = it;
		}
	}
	if(candidate != m_drawables.end()) {
		m_componentList->deleteItem(candidate->listID);
		m_sceneManager->removeDrawable(candidate->sceneID);
		m_drawables.erase(candidate);
	}
}

void SceneManager3D::update() {
	m_sceneManager->drawablesChanged();
}

