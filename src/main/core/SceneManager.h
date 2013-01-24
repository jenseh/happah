#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include <list>
#include <vector>
#include "models/Drawable.h"

using namespace std;

class SceneManager {
public:
    SceneManager();
    ~SceneManager();

    vector<Drawable*>* getDrawables();

    uint addDrawable(Drawable *drawable);
    void removeDrawable(uint id);

private:
    struct IdDrawable
    {
        unsigned int id;
        Drawable *drawable;
    };
    std::list<IdDrawable> m_drawables;
    unsigned int m_iDCounter;
};

#endif // SCENEMANAGER_H
