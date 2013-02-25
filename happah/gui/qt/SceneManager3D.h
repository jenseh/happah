#ifndef SCENEMANAGER3D_H
#define SCENEMANAGER3D_H

#include <list>
#include "happah/gui/qt/ComponentList.h"
#include "happah/gui/RenderItem3D.h"
#include "happah/scene/SceneManager.h"

class SceneManager3D : public QObject {
Q_OBJECT

public:
    struct ManagedItem
    {
        RenderItem3D* renderItem;
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
    std::list<ManagedItem> getItems();

public slots:
	void addDrawable(RenderItem3D* renderItem);
	void selectByListID(unsigned int itemID);
	void deleteCurrentDrawable(std::string name);
	void update();

signals:
	void updateTool(RenderItem3D*);
};

#endif // SCENEMANAGER3D_H
