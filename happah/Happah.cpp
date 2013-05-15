#include "happah/Happah.h"
#include "happah/HappahTypes.h"
#include "happah/geometries/gears/InvoluteGear.h"
#include "happah/triangulators/RayCloudTriangulatorBPA.h"

Happah::Happah(int& argc, char** argv)
: QApplication(argc, argv), m_sceneManager(new SceneManager()), m_defaultGUIManager(m_sceneManager) {}

Happah::~Happah() {}

int Happah::exec() {
    if(m_defaultGUIManager.init()) {
        InvoluteGear involuteGear;
        TriangleMesh3D* triangleMesh = involuteGear.toTriangleMesh();
        //RayCloud3D* rayCloud = triangleMesh->getVerticesAndNormals();
	RayCloud3D rayCloud = RayCloud3D();
	rayCloud.push_back(hpvec3(0.0, 0.0, 0.0));
	rayCloud.push_back(hpvec3(0.0, 0.0, 0.0));
	
	rayCloud.push_back(hpvec3(0.2, 0.0, 0.3));
	rayCloud.push_back(hpvec3(0.0, 0.0, 0.0));

	rayCloud.push_back(hpvec3(0.1, 0.3, 0.0));
	rayCloud.push_back(hpvec3(0.0, 0.0, 0.0));

	rayCloud.push_back(hpvec3(1.0, 1.0, 1.0));
	rayCloud.push_back(hpvec3(1.0, 1.0, 1.0));

	rayCloud.push_back(hpvec3(0.0, 2.0, 0.0));
	rayCloud.push_back(hpvec3(1.0, 1.0, 1.0));

        RayCloudTriangulatorBPA rayCloudTriangulator(0.4);
        triangleMesh = rayCloudTriangulator.triangulate(rayCloud);
        if(triangleMesh != 0)
m_defaultGUIManager.insert(TriangleMesh3D_ptr(triangleMesh));
        return QApplication::exec();
    }
    else
        return 1;
}
