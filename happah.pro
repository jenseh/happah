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
	happah/geometries/Disc.h \
	happah/geometries/Gear.h \
	happah/geometries/Geometry.h \
	happah/geometries/InvoluteGear.h \
	happah/geometries/Mesh.h\
	happah/geometries/Plane.h \
#	happah/geometries/RayCloud.h \
	happah/geometries/SimpleGear.h \
#	happah/geometries/Sphere.h \
#	happah/geometries/SpherePatch.h \
	happah/geometries/StandardProfile.h \
#	happah/geometries/TriPatch.h \
#	happah/geometries/ZCircleCloud.h \
\
	happah/gui/DrawManager.h \
	happah/gui/GearSlider.h \
	happah/gui/GUIManager.h \
	happah/gui/MainWindow.h \
	happah/gui/SceneGraphExplorerListener.h \
	happah/gui/SceneGraphExplorerPanel.h \
	happah/gui/ToolPanel.h \
	happah/gui/Viewport3D.h \
\
	happah/gui/forms/Form.h \
	happah/gui/forms/InvoluteGearForm.h \
	happah/gui/forms/InvoluteGearListener.h \
	happah/gui/forms/PlaneForm.h \
	happah/gui/forms/SimpleGearForm.h \
	happah/gui/forms/SimpleGearListener.h \
	happah/gui/forms/DiscForm.h \
	happah/gui/forms/DiscListener.h \
\
	happah/kdtree/BBox.h \
	happah/kdtree/BSphere.h \
	happah/kdtree/ExplicitKDTree.h \
	happah/kdtree/ExplicitKDTreeInnerNode.h \
	happah/kdtree/ExplicitKDTreeLeaf.h \
	happah/kdtree/ExplicitKDTreeNode.h \
\
	happah/math/Circle.h \
	happah/math/Ray.h \
	happah/math/Triangle.h \
\
	happah/scene/GUIStateNode.h \
	happah/scene/InvoluteGearNode.h \
	happah/scene/DrawVisitor.h \
	happah/scene/LineMeshNode.h\
	happah/scene/Material.h \
	happah/scene/Node.h\
	happah/scene/PlaneNode.h \
	happah/scene/PointCloudNode.h\
	happah/scene/RenderStateNode.h\
	happah/scene/SceneListener.h \
	happah/scene/SceneManager.h \
	happah/scene/SceneVisitor.h \
	happah/scene/SimpleGearNode.h \
	happah/scene/DiscNode.cpp \
	happah/scene/SimpleGeometryNode.h \
	happah/scene/TriangleMeshNode.h \
\
	happah/simulations/CircularSimulationResult.h \
#	happah/simulations/DiscGearGrind.h \
	happah/simulations/Kinematic.h \
	happah/simulations/Simulation.h \
	happah/simulations/WormGearGrind.h \
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
	happah/geometries/Disc.cpp \
	happah/geometries/Gear.cpp \
	happah/geometries/Geometry.cpp \
	happah/geometries/InvoluteGear.cpp \
	happah/geometries/Mesh.cpp\
	happah/geometries/Plane.cpp \
#	happah/geometries/RayCloud.cpp \
	happah/geometries/SimpleGear.cpp \
#	happah/geometries/Sphere.cpp \
#	happah/geometries/SpherePatch.cpp \
	happah/geometries/StandardProfile.cpp \
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
	happah/gui/forms/PlaneForm.cpp \
	happah/gui/forms/SimpleGearForm.cpp \
	happah/gui/forms/DiscForm.cpp \
\
	happah/kdtree/BBox.cpp \
	happah/kdtree/BSphere.cpp \
	happah/kdtree/ExplicitKDTree.cpp \
	happah/kdtree/ExplicitKDTreeInnerNode.cpp \
	happah/kdtree/ExplicitKDTreeLeaf.cpp \
	happah/kdtree/ExplicitKDTreeNode.cpp \
\
	happah/scene/GUIStateNode.cpp \
	happah/scene/InvoluteGearNode.cpp \
	happah/scene/LineMeshNode.cpp\
	happah/scene/Material.cpp \
	happah/scene/Node.cpp \
	happah/scene/PlaneNode.cpp \
	happah/scene/PointCloudNode.cpp\
	happah/scene/RenderStateNode.cpp\
	happah/scene/SceneManager.cpp \
	happah/scene/SimpleGearNode.cpp \
	happah/scene/DiscNode.cpp \
	happah/scene/TriangleMeshNode.cpp \
\
	happah/simulations/CircularSimulationResult.cpp \
#	happah/simulations/DiscGearGrind.cpp \
	happah/simulations/Kinematic.cpp \
	happah/simulations/Simulation.cpp \
	happah/simulations/WormGearGrind.cpp \
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
