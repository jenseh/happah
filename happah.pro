TEMPLATE = app
TARGET = happah
QT += core \
    gui \
    opengl
HEADERS += \
    src/main/gui/qt/BSplineTool.h \
    src/main/gui/qt/InvoluteSpurGearTool.h \
    src/main/gui/qt/SimpleGearTool.h \
    src/main/gui/RenderItem3D.h \
    src/main/gui/qt/GearSlider.h \
    src/main/gui/qt/ComponentList.h \
    src/main/gui/qt/EditorScene.h \
    src/main/gui/qt/EditorSceneItem.h \
    src/main/gui/qt/EditorSceneManager.h \
    src/main/gui/qt/SceneManager3D.h \
    src/main/gui/qt/Painter2DQt.h \
    src/main/gui/Painter2D.h \
    src/main/gui/Drawable2D.h \
    src/main/core/geometries/BSplineCurve.h \
    src/main/core/geometries/BSplineGearCurve.h \
    src/main/core/geometries/GeometryObject.h \
    src/main/core/geometries/Gear.h \
    src/main/core/geometries/SimpleGear.h \
    src/main/core/geometries/InvoluteSpurGear.h \
    src/main/core/geometries/ToothProfile.h \
    src/main/core/geometries/BSplineToothProfile.h \
    src/main/core/geometries/Sphere.h \
    src/main/core/geometries/StandardProfile.h \
    src/main/Happah.h \
    src/main/HappahTypes.h \
    src/main/gui/qt/MainWindow.h \
    src/main/gui/qt/SplineTool.h \
    src/main/gui/qt/Tool.h \
    src/main/gui/qt/ToolSelector.h \
    src/main/core/geometries/Grid.h \
    src/main/core/SceneManager.h \
    src/main/gui/gl/GlViewport3D.h \
    src/main/core/models/QuadMesh.h \
    src/main/core/geometries/BasicRack.h \
    src/main/core/models/Drawable.h \
    src/main/core/geometries/NonDrawable.h \
    src/main/core/models/TriangleMesh.h \
    src/main/gui/gl/DrawManager.h \
    src/main/gui/SceneListener.h \
    src/main/core/kdtree/TriangleKDTreeNode.h \
    src/main/core/kdtree/TriangleKDTree.h \
    src/main/core/kdtree/TriangleBox.h \
    src/main/core/primitives/Triangle.h \
    src/main/core/primitives/Ray.h \
    src/main/core/primitives/Color.h \
    src/main/core/kdtree/IntersectInfo.h \
    src/main/core/simulations/DiscGearGrind.h \
    src/main/core/geometries/Disc.h \
    src/main/core/kdtree/Box.h \
    src/main/core/simulations/WormGearGrind.h \
    src/main/core/models/RayCloud.h \
    src/main/core/models/CircleCloud.h \
    src/main/core/simulations/Simulation.h \
    src/main/core/primitives/Circle.h \
    src/main/core/primitives/Color.h \
    src/main/core/models/ZCircleCloud.h \
    src/main/core/simulations/Kinematic.h \
    src/main/core/kdtree/ImplicitKDTree.h \
    src/main/core/kdtree/BBox.h \
    src/main/core/kdtree/BSphere.h \
    src/main/test/CircleTriangleIntersectionBenchmark.h \
    src/main/core/kdtree/ExplicitKDTree.h \
    src/main/core/kdtree/ExplicitKDTreeNode.h \
    src/main/core/kdtree/ExplicitKDTreeLeaf.h \
    src/main/core/kdtree/ExplicitKDTreeInnerNode.h \
    src/main/test/CircleTriangleIntersectionTest.h \
    src/main/core/simulations/CircularSimulationResult.h \
    src/main/test/WormGearGrindTest.h \
    src/main/test/DiscGearGrindTest.h \
    src/main/test/KinematicTest.h \
    src/main/gui/Picker.h \
    src/main/core/models/Material.h \
    src/main/core/geometries/TriPatch.h \
    src/main/core/models/PointCloud.h \
    src/main/core/geometries/ControlNet2.h \
    src/main/gui/qt/DiscGearGrindTool.h

SOURCES += src/main/main.cpp \
    src/main/gui/qt/BSplineTool.cpp \
    src/main/gui/qt/InvoluteSpurGearTool.cpp \
    src/main/gui/qt/SimpleGearTool.cpp \
    src/main/gui/RenderItem3D.cpp \
    src/main/gui/qt/GearSlider.cpp \
    src/main/gui/qt/ComponentList.cpp \
    src/main/gui/qt/EditorScene.cpp \
    src/main/gui/qt/EditorSceneItem.cpp \
    src/main/gui/qt/EditorSceneManager.cpp \
    src/main/gui/qt/SceneManager3D.cpp \
    src/main/gui/qt/Painter2DQt.cpp \
    src/main/gui/Painter2D.cpp \
    src/main/gui/Drawable2D.cpp \
    src/main/core/geometries/BSplineCurve.cpp \
    src/main/core/geometries/BSplineGearCurve.cpp \
    src/main/core/geometries/GeometryObject.cpp \
    src/main/core/geometries/Gear.cpp \
    src/main/core/geometries/SimpleGear.cpp \
    src/main/core/geometries/InvoluteSpurGear.cpp \
    src/main/core/geometries/BSplineToothProfile.cpp \
    src/main/core/geometries/Sphere.cpp \
    src/main/core/geometries/StandardProfile.cpp \
    src/main/Happah.cpp \
    src/main/gui/qt/MainWindow.cpp \
    src/main/gui/qt/SplineTool.cpp \
    src/main/gui/qt/Tool.cpp \
    src/main/gui/qt/ToolSelector.cpp \
    src/main/core/geometries/Grid.cpp \
    src/main/core/SceneManager.cpp \
    src/main/gui/gl/GlViewport3D.cpp \
    src/main/core/models/QuadMesh.cpp \
    src/main/core/geometries/BasicRack.cpp \
    src/main/core/models/Drawable.cpp \
    src/main/core/geometries/NonDrawable.cpp \
    src/main/core/models/TriangleMesh.cpp \
    src/main/gui/gl/DrawManager.cpp \
    src/main/core/kdtree/TriangleKDTree.cpp \
    src/main/core/simulations/DiscGearGrind.cpp \
    src/main/core/geometries/Disc.cpp \
    src/main/core/kdtree/Box.cpp \
    src/main/core/simulations/WormGearGrind.cpp \
    src/main/core/models/RayCloud.cpp \
    src/main/core/models/CircleCloud.cpp \
    src/main/core/simulations/Simulation.cpp \
    src/main/core/models/ZCircleCloud.cpp \
    src/main/core/simulations/Kinematic.cpp \
    src/main/core/kdtree/ImplicitKDTree.cpp \
    src/main/core/kdtree/BBox.cpp \
    src/main/core/kdtree/BSphere.cpp \
    src/main/test/CircleTriangleIntersectionBenchmark.cpp \
    src/main/test/WormGearGrindTest.cpp \
    src/main/core/kdtree/ExplicitKDTree.cpp \
    src/main/core/kdtree/ExplicitKDTreeNode.cpp \
    src/main/core/kdtree/ExplicitKDTreeLeaf.cpp \
    src/main/core/kdtree/ExplicitKDTreeInnerNode.cpp \
    src/main/test/CircleTriangleIntersectionTest.cpp \
    src/main/test/DiscGearGrindTest.cpp \
    src/main/test/KinematicTest.cpp \
    src/main/core/simulations/CircularSimulationResult.cpp \
    src/main/gui/Picker.cpp \
    src/main/core/models/Material.cpp \
    src/main/core/geometries/TriPatch.cpp \
    src/main/core/models/PointCloud.cpp \
    src/main/core/geometries/ControlNet2.cpp \
    src/main/gui/qt/DiscGearGrindTool.cpp

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
    INCLUDEPATH += /usr/include
}

release: DESTDIR = build/release
debug:   DESTDIR = build/debug

OBJECTS_DIR = $$DESTDIR/.obj
MOC_DIR = $$DESTDIR/.moc
RCC_DIR = $$DESTDIR/.rrc
UI_DIR = $$DESTDIR/.ui
