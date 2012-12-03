#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include <vector>
#include "models/Model.h"
#include "geometries/GeometryObject.h"
#include "geometries/Grid.h"
#include "geometries/Sphere.h"
#include "geometries/Gear.h"

// Qt includes are only for the timer
#include <QGLShaderProgram>

using namespace std;

class SceneManager {
public:
    SceneManager();
    ~SceneManager();

    vector<QuadliteralMesh*> getQuadliteralMeshs();

private:
   vector<QuadliteralMesh*> quadliteralMeshs_;

    QTimer *timer_;
    const static int WAIT_TIME = 40;

   //Just for the beginning to have some objects
   QuadliteralMesh* gear1_;
   QuadliteralMesh* gear2_;
   QuadliteralMesh* sphere_;
   QuadliteralMesh* grid_;

private slots:
   void update();
};

#endif // SCENEMANAGER_H
