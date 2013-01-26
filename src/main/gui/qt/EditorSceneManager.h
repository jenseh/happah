#ifndef EDITORSCENEMANAGER_H
#define EDITORSCENEMANAGER_H

#include <list>

#include "EditorScene.h"
#include "EditorSceneItem.h"
#include "ComponentList.h"
#include "../Drawable2D.h"

class EditorSceneManager : public QObject {
Q_OBJECT

private:
	struct ManagedItem
	{
		Drawable2D* drawable;
		EditorSceneItem* sceneItem;
		unsigned int listID;
		bool active;
	};

private:
	EditorScene* m_scene;
	ComponentList* m_componentList;
	std::list<ManagedItem> m_drawables;

public:
	EditorSceneManager( EditorScene* scene, ComponentList* list );

public slots:
	void addDrawable( Drawable2D* drawable );
	void selectByListID( unsigned int itemID );
	void deleteCurrentDrawable();

};

#endif // EDITORSCENEMANAGER_H
