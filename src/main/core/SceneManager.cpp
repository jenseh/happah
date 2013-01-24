#include "SceneManager.h"
#include <time.h>
#include "../test/WormGearGrindTest.h"

SceneManager::SceneManager() : m_iDCounter(0) {
}

SceneManager::~SceneManager() {
}

//first idDrawable gets id 0, m_idCounter is has number of produced idDrawables
uint SceneManager::addDrawable(Drawable *drawable) {
    IdDrawable  idDrawable = {m_iDCounter, drawable};
    m_drawables.push_back(idDrawable);
    m_iDCounter += 1;
    return idDrawable.id;
}

void SceneManager::removeDrawable(uint id) {
    for(std::list<IdDrawable>::iterator it = m_drawables.begin(); it != m_drawables.end(); ++it) {
        if (it->id == id) {
            m_drawables.erase(it);
        }
    }
}

vector<Drawable*>* SceneManager::getDrawables() {
    std::vector<Drawable*> *drawables = new std::vector<Drawable*>;

    for(std::list<IdDrawable>::iterator it = m_drawables.begin(); it != m_drawables.end(); ++it) {
        drawables->push_back(it->drawable);
    }
    return drawables;
}
