#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include <vector>
#include "models/Drawable.h"
#include "geometries/GeometryObject.h"
#include "geometries/Grid.h"
#include "geometries/Sphere.h"
#include "geometries/SpurGear.h"
#include "geometries/BasicRack.h"

// Qt includes are only for the timer
#include <QGLShaderProgram>

using namespace std;

class SceneManager {
public:
    SceneManager();
    ~SceneManager();

    vector<Drawable*>* getDrawables();

private:
   vector<Drawable*>* drawables_;

    QTimer *timer_;
    const static int WAIT_TIME = 40;

   //Just for the beginning to have some objects
   Drawable* gear1_;
   Drawable* gear2_;
   Drawable* sphere_;
   Drawable* grid_;
   Drawable* rack1_;

private slots:
   void update();
};

#endif // SCENEMANAGER_H