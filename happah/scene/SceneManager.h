#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include <list>
#include <memory>
#include <vector>

#include "happah/geometries/InvoluteSpurGear.h"
#include "happah/geometries/NonDrawable.h"
#include "happah/gui/SceneListener.h"
#include "happah/models/Drawable.h"
#include "happah/scene/Node.h"
#include "happah/scene/InvoluteSpurGearNode.h"
#include "happah/scene/SceneVisitor.h"
#include "happah/scene/TriangleMeshNode.h"
#include "happah/scene/TriangleMeshRenderStateNode.h"

using namespace std;



class SceneManager : public Node, public SceneVisitor {

public:
	SceneManager();
	~SceneManager();

	void add(InvoluteSpurGear_ptr involuteSpurGear, TriangleMesh_ptr triangleMesh);
	void remove(InvoluteSpurGear_ptr involuteSpurGear, TriangleMesh_ptr triangleMesh);
	void visit(InvoluteSpurGearNode& involuteSpurGearNode);
	void visit(TriangleMeshNode& triangleMeshNode);
	void visit(TriangleMeshRenderStateNode& triangleMeshRenderStateNode);
    vector<Drawable*>* getDrawables();

    uint addDrawable(Drawable *drawable);
    void removeDrawable(uint id);
    void drawablesChanged();

    void addNonDrawable(NonDrawable *nonDrawable);
    vector<NonDrawable*>* getNonDrawables();

    void registerListener(SceneListener* sceneListener);

private:
	vector<Drawable*>* m_vectorDrawables;

    struct IdDrawable
    {
        unsigned int id;
        Drawable *drawable;
    };
    struct IdNonDrawable
    {
      unsigned int id;
       NonDrawable *nonDrawable;
    };
    std::list<SceneListener*> m_listeners;
    std::list<IdDrawable> m_drawables;
    std::list<IdNonDrawable> m_nonDrawables;
    unsigned int m_iDCounter;
    unsigned int m_iDNCounter;
    void notifyListeners();
};

#endif // SCENEMANAGER_H
