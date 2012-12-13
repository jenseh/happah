#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include <vector>
#include "models/Drawable.h"
#include "geometries/GeometryObject.h"
#include "geometries/Grid.h"
#include "geometries/Sphere.h"
#include "geometries/Gear.h"
#include "geometries/BasicRack.h"

// Qt includes are only for the timer
#include <QGLShaderProgram>

using namespace std;

class SceneManager {
public:
    SceneManager();
    ~SceneManager();

    vector<QuadMesh*> getQuadMeshs();

private:
   vector<QuadMesh*> quadMeshs_;

    QTimer *timer_;
    const static int WAIT_TIME = 40;

   //Just for the beginning to have some objects
   QuadMesh* gear1_;
   QuadMesh* gear2_;
   QuadMesh* sphere_;
   QuadMesh* grid_;
   QuadMesh* rack1_;

private slots:
   void update();
};

#endif // SCENEMANAGER_H
