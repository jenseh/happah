#include "happah/gui/qt/EditorSceneManager.h"

EditorSceneManager::EditorSceneManager( EditorScene* scene, ComponentList* list )
		: m_scene(scene), m_componentList(list)
{
	connect( m_componentList, SIGNAL( selectionChanged(unsigned int) ), this, SLOT( selectByListID(unsigned int) ) );

}

void EditorSceneManager::addDrawable( Drawable2D* drawable ) {
	ManagedItem item;
	item.drawable = drawable;
	item.sceneItem = new EditorSceneItem(drawable);
	m_scene->addItem(item.sceneItem);
	item.listID = m_componentList->addNewItem(drawable->getName());
	m_componentList->selectItem(item.listID);
	for( std::list<ManagedItem>::iterator it = m_drawables.begin();
	          it != m_drawables.end();
	          ++it )
	{
		it->active=false;
	}
	item.active = true;

	m_drawables.push_back(item);
}

void EditorSceneManager::selectByListID( unsigned int itemID ) {
	for( std::list<ManagedItem>::iterator it = m_drawables.begin();
	          it != m_drawables.end();
	          ++it )
	{
		it->active = it->listID == itemID;
		if (it->active) {
			emit updateTool(it->drawable);
		}
	}
}

void EditorSceneManager::deleteCurrentDrawable( std::string name ) {
	std::list<ManagedItem>::iterator candidate = m_drawables.end();
	for( std::list<ManagedItem>::iterator it = m_drawables.begin();
	          it != m_drawables.end();
	          ++it )
	{
		if( it->active && it->drawable->getName() == name ) {
			candidate = it;
		}
	}
	if( candidate != m_drawables.end() ) {
		m_componentList->deleteItem( candidate->listID );
		m_scene->removeItem( candidate->sceneItem );
		m_drawables.erase( candidate );
	}
}

