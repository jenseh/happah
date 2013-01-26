#include "SceneManager.h"
#include <time.h>
#include "../test/WormGearGrindTest.h"
#include <iostream>


SceneManager::SceneManager() : m_iDCounter(0) {
    std::cout << " SM: size" << m_drawables.size()<< std::endl;
//    new WormGearGrindTest();
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
    std::list<IdDrawable>::iterator candidate = m_drawables.end();
    for(std::list<IdDrawable>::iterator it = m_drawables.begin(), eend = m_drawables.end(); it != eend; ++it) {
        if (it->id == id) {
            candidate = it;
        }
    }
    if(candidate != m_drawables.end()){
        m_drawables.erase(candidate);
        m_deletedCounter += 1;
    }
}

vector<Drawable*>* SceneManager::getDrawables() {
    std::vector<Drawable*> *drawables = new std::vector<Drawable*>;

    for(std::list<IdDrawable>::iterator it = m_drawables.begin(); it != m_drawables.end(); ++it) {
        drawables->push_back(it->drawable);
    }
    return drawables;
}

unsigned int SceneManager::getObjectState() {
    return m_iDCounter + m_deletedCounter;
}
