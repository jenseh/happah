TEMPLATE = app
TARGET = happah
QT += core \
	gui \
	opengl

#KEEP HEADERS SORTED!!!
HEADERS += \
	happah/Happah.h \
	happah/HappahTypes.h \
\
	happah/geometries/BasicRack.h \
	happah/geometries/BSplineCurve.h \
	happah/geometries/BSplineGearCurve.h \
	happah/geometries/ControlNet2.h \
	happah/geometries/Disc.h \
	happah/geometries/Gear.h \
	happah/geometries/GeometryObject.h \
	happah/geometries/Grid.h \
	happah/geometries/InvoluteSpurGear.h \
	happah/geometries/NonDrawable.h \
	happah/geometries/SimpleGear.h \
	happah/geometries/Sphere.h \
	happah/geometries/SpherePatch.h \
	happah/geometries/StandardProfile.h \
	happah/geometries/TriPatch.h \
\
	happah/gui/Drawable2D.h \
	happah/gui/Painter2D.h \
	happah/gui/Picker.h \
	happah/gui/RenderItem3D.h \
	happah/gui/SceneListener.h \
\
	happah/gui/gl/DrawManager.h \
	happah/gui/gl/GlViewport3D.h \
\
	happah/gui/qt/BSplineTool.h \
	happah/gui/qt/ComponentList.h \
	happah/gui/qt/DiscGearGrindTool.h \
	happah/gui/qt/EditorScene.h \
	happah/gui/qt/EditorSceneItem.h \
	happah/gui/qt/EditorSceneManager.h \
	happah/gui/qt/GearSlider.h \
	happah/gui/qt/InvoluteSpurGearTool.h \
	happah/gui/qt/MainWindow.h \
	happah/gui/qt/Painter2DQt.h \
	happah/gui/qt/SceneManager3D.h \
	happah/gui/qt/SimpleGearTool.h \
	happah/gui/qt/SplineTool.h \
	happah/gui/qt/Tool.h \
	happah/gui/qt/ToolSelector.h \
\
	happah/kdtree/BBox.h \
	happah/kdtree/Box.h \
	happah/kdtree/BSphere.h \
	happah/kdtree/ExplicitKDTree.h \
	happah/kdtree/ExplicitKDTreeInnerNode.h \
	happah/kdtree/ExplicitKDTreeLeaf.h \
	happah/kdtree/ExplicitKDTreeNode.h \
	happah/kdtree/ImplicitKDTree.h \
	happah/kdtree/IntersectInfo.h \
	happah/kdtree/TriangleBox.h \
	happah/kdtree/TriangleKDTree.h \
	happah/kdtree/TriangleKDTreeNode.h \
\
	happah/models/CircleCloud.h \
	happah/models/Drawable.h \
	happah/models/GeometryMesh.h \
	happah/models/Material.h \
	happah/models/PointCloud.h \
	happah/models/QuadMesh.h \
	happah/models/RayCloud.h \
	happah/models/TriangleMesh.h \
	happah/models/ZCircleCloud.h \
\
	happah/primitives/Circle.h \
	happah/primitives/Color.h \
	happah/primitives/Ray.h \
	happah/primitives/Triangle.h \
\
	happah/scene/SceneManager.h \
\
	happah/simulations/CircularSimulationResult.h \
	happah/simulations/DiscGearGrind.h \
	happah/simulations/Kinematic.h \
	happah/simulations/Simulation.h \
	happah/simulations/WormGearGrind.h

#KEEP SOURCES SORTED!!!
SOURCES += \
	happah/main.cpp \
	happah/Happah.cpp \
\
	happah/geometries/BasicRack.cpp \
	happah/geometries/BSplineCurve.cpp \
	happah/geometries/BSplineGearCurve.cpp \
	happah/geometries/ControlNet2.cpp \
	happah/geometries/Disc.cpp \
	happah/geometries/Gear.cpp \
	happah/geometries/GeometryObject.cpp \
	happah/geometries/Grid.cpp \
	happah/geometries/InvoluteSpurGear.cpp \
	happah/geometries/NonDrawable.cpp \
	happah/geometries/SimpleGear.cpp \
	happah/geometries/Sphere.cpp \
	happah/geometries/SpherePatch.cpp \
	happah/geometries/StandardProfile.cpp \
	happah/geometries/TriPatch.cpp \
\
	happah/gui/Drawable2D.cpp \
	happah/gui/Painter2D.cpp \
	happah/gui/Picker.cpp \
	happah/gui/RenderItem3D.cpp \
\
	happah/gui/gl/DrawManager.cpp \
	happah/gui/gl/GlViewport3D.cpp \
\
	happah/gui/qt/BSplineTool.cpp \
	happah/gui/qt/ComponentList.cpp \
	happah/gui/qt/DiscGearGrindTool.cpp \
	happah/gui/qt/EditorScene.cpp \
	happah/gui/qt/EditorSceneItem.cpp \
	happah/gui/qt/EditorSceneManager.cpp \
	happah/gui/qt/GearSlider.cpp \
	happah/gui/qt/InvoluteSpurGearTool.cpp \
	happah/gui/qt/MainWindow.cpp \
	happah/gui/qt/Painter2DQt.cpp \
	happah/gui/qt/SceneManager3D.cpp \
	happah/gui/qt/SimpleGearTool.cpp \
	happah/gui/qt/SplineTool.cpp \
	happah/gui/qt/Tool.cpp \
	happah/gui/qt/ToolSelector.cpp \
\
	happah/kdtree/BBox.cpp \
	happah/kdtree/Box.cpp \
	happah/kdtree/BSphere.cpp \
	happah/kdtree/ExplicitKDTree.cpp \
	happah/kdtree/ExplicitKDTreeInnerNode.cpp \
	happah/kdtree/ExplicitKDTreeLeaf.cpp \
	happah/kdtree/ExplicitKDTreeNode.cpp \
	happah/kdtree/ImplicitKDTree.cpp \
	happah/kdtree/TriangleKDTree.cpp \
\
	happah/models/CircleCloud.cpp \
	happah/models/Drawable.cpp \
	happah/models/GeometryMesh.cpp \
	happah/models/Material.cpp \
	happah/models/PointCloud.cpp \
	happah/models/QuadMesh.cpp \
	happah/models/RayCloud.cpp \
	happah/models/TriangleMesh.cpp \
	happah/models/ZCircleCloud.cpp \
\
	happah/scene/SceneManager.cpp \
\
	happah/simulations/CircularSimulationResult.cpp \
	happah/simulations/DiscGearGrind.cpp \
	happah/simulations/Kinematic.cpp \
	happah/simulations/Simulation.cpp \
	happah/simulations/WormGearGrind.cpp

FORMS += 
RESOURCES += 

win32 {
	QMAKE_CXXFLAGS += -fexceptions -DGL_GLEXT_PROTOTYPES
	CONFIG += exceptions
	LIBS += -lglew32
	INCLUDEPATH += ../include
}

unix {
	LIBS += -lGLEW
	INCLUDEPATH += /usr/include $$system(pwd)
}

release: DESTDIR = build/release
debug:   DESTDIR = build/debug

OBJECTS_DIR = $$DESTDIR/.obj
MOC_DIR = $$DESTDIR/.moc
RCC_DIR = $$DESTDIR/.rrc
UI_DIR = $$DESTDIR/.ui
