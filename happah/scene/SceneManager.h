#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include <list>
#include <vector>
#include "models/Drawable.h"
#include "geometries/NonDrawable.h"
#include "../gui/SceneListener.h"

using namespace std;

class SceneManager {
public:
    SceneManager();
    ~SceneManager();

    vector<Drawable*>* getDrawables();

    uint addDrawable(Drawable *drawable);
    void removeDrawable(uint id);
    void drawablesChanged();

    void addNonDrawable(NonDrawable *nonDrawable);
    vector<NonDrawable*>* getNonDrawables();


    void buildScene();
    void registerListener(SceneListener* sceneListener);

private:
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
