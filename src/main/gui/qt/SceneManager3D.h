#ifndef SCENEMANAGER3D_H
#define SCENEMANAGER3D_H

#include <list>
#include "ComponentList.h"
#include "../../core/models/Drawable.h"
#include "../../core/SceneManager.h"

class SceneManager3D : public QObject {
Q_OBJECT

private:
	struct ManagedItem
	{
		Drawable* drawable;
		unsigned int sceneID;
		unsigned int listID;
		bool active;
	};

private:
	SceneManager* m_sceneManager;
	ComponentList* m_componentList;
	std::list<ManagedItem> m_drawables;

public:
	SceneManager3D(SceneManager* sceneManager, ComponentList* list);

public slots:
	void addDrawable(Drawable* drawable);
	void selectByListID(unsigned int itemID);
	void deleteCurrentDrawable();
	void update();

};

#endif // SCENEMANAGER3D_H
