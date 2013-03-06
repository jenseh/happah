TEMPLATE = app
TARGET = happah
CONFIG -= release
QT += core \
	gui \
	opengl

#KEEP HEADERS SORTED!!!
HEADERS += \
	happah/Happah.h \
	happah/HappahTypes.h \
\
#	happah/geometries/BasicRack.h \
	happah/geometries/BSplineCurve.h \
	happah/geometries/BSplineGearCurve.h \
#	happah/geometries/CircleCloud.h \
#	happah/geometries/ControlNet2.h \
#	happah/geometries/Disc.h \
	happah/geometries/Gear.h \
	happah/geometries/GeometryObject.h \
#	happah/geometries/Grid.h \
	happah/geometries/InvoluteGear.h \
	happah/geometries/Mesh.h\
	happah/geometries/Plane.h \
#	happah/geometries/RayCloud.h \
	happah/geometries/SimpleGear.h \
#	happah/geometries/Sphere.h \
#	happah/geometries/SpherePatch.h \
#	happah/geometries/StandardProfile.h \
#	happah/geometries/TriPatch.h \
#	happah/geometries/ZCircleCloud.h \
\
	happah/gui/DrawManager.h \
	happah/gui/GearSlider.h \
	happah/gui/GUIManager.h \
	happah/gui/MainWindow.h \
	happah/gui/SceneGraphExplorerPanel.h \
	happah/gui/ToolPanel.h \
	happah/gui/Viewport3D.h \
\
	happah/gui/forms/Form.h \
	happah/gui/forms/InvoluteGearForm.h \
	happah/gui/forms/InvoluteGearListener.h \
\
#	happah/kdtree/BBox.h \
#	happah/kdtree/Box.h \
#	happah/kdtree/BSphere.h \
#	happah/kdtree/ExplicitKDTree.h \
#	happah/kdtree/ExplicitKDTreeInnerNode.h \
#	happah/kdtree/ExplicitKDTreeLeaf.h \
#	happah/kdtree/ExplicitKDTreeNode.h \
#	happah/kdtree/ImplicitKDTree.h \
#	happah/kdtree/IntersectInfo.h \
#	happah/kdtree/TriangleBox.h \
#	happah/kdtree/TriangleKDTree.h \
#	happah/kdtree/TriangleKDTreeNode.h \
\
	happah/primitives/Circle.h \
	happah/primitives/Color.h \
	happah/primitives/Ray.h \
	happah/primitives/Triangle.h \
\
	happah/scene/GUIStateNode.h \
	happah/scene/InvoluteGearNode.h \
	happah/scene/DrawVisitor.h \
	happah/scene/LineMeshNode.h\
	happah/scene/Material.h \
	happah/scene/Node.h\
	happah/scene/PointCloudNode.h\
	happah/scene/RenderStateNode.h\
	happah/scene/SceneListener.h \
	happah/scene/SceneManager.h \
	happah/scene/SceneVisitor.h \
	happah/scene/SimpleGeometryNode.h \
	happah/scene/TriangleMeshNode.h \
\
#	happah/simulations/CircularSimulationResult.h \
#	happah/simulations/DiscGearGrind.h \
#	happah/simulations/Kinematic.h \
#	happah/simulations/Simulation.h \
#	happah/simulations/WormGearGrind.h \
\
	happah/transformations/RigidAffineTransformation.h

#KEEP SOURCES SORTED!!!
SOURCES += \
	happah/main.cpp \
	happah/Happah.cpp \
\
#	happah/geometries/BasicRack.cpp \
	happah/geometries/BSplineCurve.cpp \
	happah/geometries/BSplineGearCurve.cpp \
#	happah/geometries/CircleCloud.cpp \
#	happah/geometries/ControlNet2.cpp \
#	happah/geometries/Disc.cpp \
	happah/geometries/Gear.cpp \
	happah/geometries/GeometryObject.cpp \
#	happah/geometries/Grid.cpp \
	happah/geometries/InvoluteGear.cpp \
	happah/geometries/Mesh.cpp\
	happah/geometries/Plane.cpp \
#	happah/geometries/RayCloud.cpp \
	happah/geometries/SimpleGear.cpp \
#	happah/geometries/Sphere.cpp \
#	happah/geometries/SpherePatch.cpp \
#	happah/geometries/StandardProfile.cpp \
#	happah/geometries/TriPatch.cpp \
#	happah/geometries/ZCircleCloud.cpp \
\
	happah/gui/DrawManager.cpp \
	happah/gui/GearSlider.cpp \
	happah/gui/GUIManager.cpp \
	happah/gui/MainWindow.cpp \
	happah/gui/SceneGraphExplorerPanel.cpp \
	happah/gui/ToolPanel.cpp \
	happah/gui/Viewport3D.cpp \
\
	happah/gui/forms/Form.cpp \
	happah/gui/forms/InvoluteGearForm.cpp \
\
#	happah/kdtree/BBox.cpp \
#	happah/kdtree/Box.cpp \
#	happah/kdtree/BSphere.cpp \
#	happah/kdtree/ExplicitKDTree.cpp \
#	happah/kdtree/ExplicitKDTreeInnerNode.cpp \
#	happah/kdtree/ExplicitKDTreeLeaf.cpp \
#	happah/kdtree/ExplicitKDTreeNode.cpp \
#	happah/kdtree/ImplicitKDTree.cpp \
#	happah/kdtree/TriangleKDTree.cpp \
\
	happah/scene/GUIStateNode.cpp \
	happah/scene/InvoluteGearNode.cpp \
	happah/scene/LineMeshNode.cpp\
	happah/scene/Material.cpp \
	happah/scene/Node.cpp \
	happah/scene/PointCloudNode.cpp\
	happah/scene/RenderStateNode.cpp\
	happah/scene/SceneManager.cpp \
	happah/scene/TriangleMeshNode.cpp \
\
#	happah/simulations/CircularSimulationResult.cpp \
#	happah/simulations/DiscGearGrind.cpp \
#	happah/simulations/Kinematic.cpp \
#	happah/simulations/Simulation.cpp \
#	happah/simulations/WormGearGrind.cpp \
\
	happah/transformations/RigidAffineTransformation.cpp

FORMS += 
RESOURCES += 

win32 {
	QMAKE_CXXFLAGS += -fexceptions -DGL_GLEXT_PROTOTYPES
	CONFIG += exceptions
	LIBS += -lglew32
	INCLUDEPATH += ../include
}

unix {
	QMAKE_CXXFLAGS += -std=c++0x
	LIBS += -lGLEW
	INCLUDEPATH += /usr/include $$system(pwd)
}

CONFIG(debug) {
	DESTDIR = build/debug
}

CONFIG(release) {
	DESTDIR = build/release
}

OBJECTS_DIR = $$DESTDIR/.obj
MOC_DIR = $$DESTDIR/.moc
RCC_DIR = $$DESTDIR/.rrc
UI_DIR = $$DESTDIR/.ui
