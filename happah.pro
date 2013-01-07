TEMPLATE = app
TARGET = happah
QT += core \
    gui \
    opengl
HEADERS += src/main/gui/qt/BSplineComponent.h \
    src/main/gui/qt/BSplineTool.h \
    src/main/gui/qt/Component.h \
    src/main/gui/qt/ComponentContainer.h \
    src/main/core/geometries/GeometryObject.h \
    src/main/core/geometries/SpurGear.h \
    src/main/core/geometries/Sphere.h \
    src/main/core/geometries/StandardProfile.h \
    src/main/gui/qt/EditorScene.h \
    src/main/Happah.h \
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
    src/main/gui/gl/DrawManagerItem.h \
    src/main/core/kdtree/TriangleKDTreeNode.h \
    src/main/core/kdtree/TriangleKDTree.h \
    src/main/core/kdtree/TriangleBox.h \
    src/main/core/primitives/Triangle.h \
    src/main/core/primitives/Ray.h \
    src/main/core/kdtree/IntersectInfo.h \
    src/main/core/simulations/DiscGearGrind.h \
    src/main/core/geometries/Disc.h \
    src/main/core/kdtree/Box.h \
    src/main/core/simulations/WormGearGrind.h \
    src/main/core/models/RayCloud.h \
    src/main/core/models/CircleCloud.h \
    src/main/core/simulations/Simulation.h \
    src/main/core/primitives/Circle.h \
    src/main/core/primitives/Color.h
SOURCES += src/main/main.cpp \
    src/main/gui/qt/BSplineComponent.cpp \
    src/main/gui/qt/BSplineTool.cpp \
    src/main/gui/qt/Component.cpp \
    src/main/gui/qt/ComponentContainer.cpp \
    src/main/core/geometries/GeometryObject.cpp \
    src/main/core/geometries/SpurGear.cpp \
    src/main/core/geometries/Sphere.cpp \
    src/main/core/geometries/StandardProfile.cpp \
    src/main/gui/qt/EditorScene.cpp \
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
    src/main/gui/gl/DrawManagerItem.cpp \
    src/main/core/kdtree/TriangleKDTree.cpp \
    src/main/core/simulations/DiscGearGrind.cpp \
    src/main/core/geometries/Disc.cpp \
    src/main/core/kdtree/Box.cpp \
    src/main/core/simulations/WormGearGrind.cpp \
    src/main/core/models/RayCloud.cpp \
    src/main/core/models/CircleCloud.cpp \
    src/main/core/simulations/Simulation.cpp
FORMS += 
RESOURCES += 
INCLUDEPATH += /usr/include



