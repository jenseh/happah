#include "happah/Happah.h"

#include "io/WavefrontGeometryReaderOBJ.h"
#include <fstream>

#include "transformations/DeformationTransferer.h"
#include "transformations/TriangleMeshTransformation.h"
#include "kdtreeLib/NearestNeighbor.h"

Happah::Happah(int& argc, char** argv)
    : QApplication(argc, argv), m_sceneManager(new SceneManager()), m_defaultGUIManager(m_sceneManager) {}

Happah::~Happah() {}

int Happah::exec() {
    if(m_defaultGUIManager.init()) {

        QString pathSource = QString("/home/joschi/models/horse-poses/horse-reference.triangle.mesh.3d.obj");
        TriangleMesh3D* sourceMesh;
        ifstream file1(pathSource.toStdString().c_str());
        WavefrontGeometryReaderOBJ::read(file1, sourceMesh);

        QString pathTarget = QString("/home/joschi/models/horse-poses/horse-01.triangle.mesh.3d.obj");
        TriangleMesh3D* targetMesh;
        ifstream file2(pathTarget.toStdString().c_str());
        WavefrontGeometryReaderOBJ::read(file2, targetMesh);

        TriangleMesh3D_ptr sourceMesh_ptr(sourceMesh);
        TriangleMesh3D_ptr targetMesh_ptr(targetMesh);


        TriangleMeshTransformation_ptr deformation = DeformationTransferer::computeTransformation(sourceMesh_ptr, targetMesh_ptr);
        TriangleMesh3D_ptr deformedMesh = deformation->transform(sourceMesh_ptr);

        if(sourceMesh != 0)
            m_defaultGUIManager.insert(sourceMesh_ptr);

        if(deformedMesh != 0)
            m_defaultGUIManager.insert(deformedMesh);


        // Nearest Neighbor
        TriangleKDTree *tree = NearestNeighbor::generateTriangleKDTree(sourceMesh_ptr);

        // Test: Print Neighbor Triangles for each Triangle
        vector<hpuint> *triangleIds;
        for (size_t i = 0; i < sourceMesh->getIndices()->size()/3; ++i) {
            triangleIds = NearestNeighbor::trianglesWithinRange(sourceMesh_ptr, i, 0.02, *tree);
            stringstream  s;
            const string delimiter=",";
            copy(triangleIds->begin(),triangleIds->end(), ostream_iterator<hpuint>(s,delimiter.c_str()));
            std::cout << s.str() << "\n" << endl;

            free(triangleIds);
        }

        free(tree);

        return QApplication::exec();
    }
    else
        return 1;
}
