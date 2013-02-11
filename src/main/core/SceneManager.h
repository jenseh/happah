#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include <list>
#include <vector>
#include "models/Drawable.h"
#include "geometries/NonDrawable.h"

using namespace std;

class SceneManager {
public:
    SceneManager();
    ~SceneManager();

    vector<Drawable*>* getDrawables();

    uint addDrawable(Drawable *drawable);
    void removeDrawable(uint id);

    unsigned int getObjectState();
    void buildScene();

    void addNonDrawable(NonDrawable *nonDrawable);
    vector<NonDrawable*>* getNonDrawables();

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

    std::list<IdNonDrawable> m_nonDrawables;
    std::list<IdDrawable> m_drawables;
    unsigned int m_iDCounter;
    unsigned int m_iDNCounter;
    unsigned int m_deletedCounter;
};

#endif // SCENEMANAGER_H
