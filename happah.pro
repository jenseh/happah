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
	happah/geometries/PointCloud.h\
#	happah/geometries/RayCloud.h \
	happah/geometries/SimpleGear.h \
#	happah/geometries/Sphere.h \
	happah/geometries/SpherePatch.h \
	happah/geometries/StandardProfile.h \
#	happah/geometries/TriPatch.h \
	happah/geometries/Worm.h \
#	happah/geometries/ZCircleCloud.h \
\
	happah/gui/DefaultGUIManager.h \
	happah/gui/DrawManager.h \
	happah/gui/Slider.h \
	happah/gui/GUIManager.h \
	happah/gui/MainWindow.h \
	happah/gui/SceneGraphExplorerListener.h \
	happah/gui/SceneGraphExplorerPanel.h \
	happah/gui/ToolPanel.h \
	happah/gui/VectorInput.h \
	happah/gui/Viewport3D.h \
\
	happah/gui/context-menus/ContextMenu.h \
	happah/gui/context-menus/InvoluteGearContextMenu.h \
\
	happah/gui/forms/Form.h \
	happah/gui/forms/InvoluteGearForm.h \
	happah/gui/forms/PlaneForm.h \
	happah/gui/forms/SimpleGearForm.h \
	happah/gui/forms/SpherePatchForm.h \
	happah/gui/forms/DiscForm.h \
	happah/gui/forms/SimulationForm.h \
	happah/gui/forms/WormForm.h \
\
	happah/kdtree/BBox.h \
	happah/kdtree/BSphere.h \
	happah/kdtree/KDTree.h \
	happah/kdtree/KDTreeInnerNode.h \
	happah/kdtree/KDTreeLeaf.h \
	happah/kdtree/KDTreeNode.h \
\
#	happah/math/Circle.h \
	happah/math/Ray.h \
	happah/math/Triangle.h \
\
	happah/scene/ElementRenderStateNode.h\
	happah/scene/GUIStateNode.h \
	happah/scene/InvoluteGearNode.h \
	happah/scene/DrawVisitor.h \
	happah/scene/LineMeshNode.h\
	happah/scene/Material.h \
	happah/scene/Node.h\
	happah/scene/PlaneNode.h \
	happah/scene/PointCloudNode.h\
	happah/scene/PointCloudRenderStateNode.h\
	happah/scene/RenderStateNode.h\
	happah/scene/SceneListener.h \
	happah/scene/SceneManager.h \
	happah/scene/SceneVisitor.h \
	happah/scene/SimpleGearNode.h \
	happah/scene/SpherePatchNode.h\
	happah/scene/DiscNode.cpp \
	happah/scene/WormNode.cpp \
	happah/scene/SimpleGeometryNode.h \
	happah/scene/TriangleMeshNode.h \
\
	happah/simulations/CircularSimulationResult.h \
	happah/simulations/DiscGearGrind.h \
	happah/simulations/Kinematic.h \
	happah/simulations/Simulation.h \
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
	happah/geometries/Disc.cpp \
	happah/geometries/Gear.cpp \
	happah/geometries/Geometry.cpp \
	happah/geometries/InvoluteGear.cpp \
	happah/geometries/Mesh.cpp\
	happah/geometries/Plane.cpp \
	happah/geometries/PointCloud.cpp\
#	happah/geometries/RayCloud.cpp \
	happah/geometries/SimpleGear.cpp \
#	happah/geometries/Sphere.cpp \
	happah/geometries/SpherePatch.cpp \
	happah/geometries/StandardProfile.cpp \
#	happah/geometries/TriPatch.cpp \
	happah/geometries/Worm.cpp \
#	happah/geometries/ZCircleCloud.cpp \
\
	happah/gui/DefaultGUIManager.cpp \
	happah/gui/DrawManager.cpp \
	happah/gui/Slider.cpp \
	happah/gui/MainWindow.cpp \
	happah/gui/SceneGraphExplorerPanel.cpp \
	happah/gui/ToolPanel.cpp \
	happah/gui/VectorInput.cpp \
	happah/gui/Viewport3D.cpp \
\
	happah/gui/context-menus/ContextMenu.cpp \
	happah/gui/context-menus/InvoluteGearContextMenu.cpp \
\
	happah/gui/forms/Form.cpp \
	happah/gui/forms/InvoluteGearForm.cpp \
	happah/gui/forms/PlaneForm.cpp \
	happah/gui/forms/SimpleGearForm.cpp \
	happah/gui/forms/SimulationForm.cpp \
	happah/gui/forms/SpherePatchForm.cpp \
	happah/gui/forms/DiscForm.cpp \
	happah/gui/forms/WormForm.cpp \
\
	happah/kdtree/BBox.cpp \
	happah/kdtree/BSphere.cpp \
	happah/kdtree/KDTree.cpp \
	happah/kdtree/KDTreeInnerNode.cpp \
	happah/kdtree/KDTreeLeaf.cpp \
	happah/kdtree/KDTreeNode.cpp \
\
	happah/math/Ray.cpp \
\
	happah/scene/ElementRenderStateNode.cpp\
	happah/scene/GUIStateNode.cpp \
	happah/scene/InvoluteGearNode.cpp \
	happah/scene/LineMeshNode.cpp\
	happah/scene/Material.cpp \
	happah/scene/Node.cpp \
	happah/scene/PlaneNode.cpp \
	happah/scene/PointCloudRenderStateNode.cpp\
	happah/scene/PointCloudNode.cpp\
	happah/scene/RenderStateNode.cpp\
	happah/scene/SceneManager.cpp \
	happah/scene/SimpleGearNode.cpp \
	happah/scene/SpherePatchNode.cpp\
	happah/scene/DiscNode.cpp \
	happah/scene/WormNode.cpp \
	happah/scene/TriangleMeshNode.cpp \
\
	happah/simulations/CircularSimulationResult.cpp \
	happah/simulations/DiscGearGrind.cpp \
	happah/simulations/Kinematic.cpp \
	happah/simulations/Simulation.cpp \
#	happah/simulations/WormGearGrind.cpp \
\
	happah/transformations/RigidAffineTransformation.cpp

FORMS += 
RESOURCES += 

win32 {
	QMAKE_CXXFLAGS += -std=c++0x -U__STRICT_ANSI__ -DGL_GLEXT_PROTOTYPES
	LIBS += -lglew32
	INCLUDEPATH += ./
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
