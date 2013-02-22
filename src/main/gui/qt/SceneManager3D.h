#ifndef SCENEMANAGER3D_H
#define SCENEMANAGER3D_H

#include <list>
#include "ComponentList.h"
#include "../RenderItem3D.h"
#include "../../core/SceneManager.h"

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
