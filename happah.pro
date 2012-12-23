TEMPLATE = app
TARGET = happah
QT += core \
    gui \
    opengl
HEADERS += src/main/BSplineComponent.h \
    src/main/BSplineTool.h \
    src/main/Component.h \
    src/main/ComponentContainer.h \
    src/main/core/geometries/GeometryObject.h \
    src/main/core/geometries/SpurGear.h \
    src/main/core/geometries/Sphere.h \
    src/main/core/geometries/StandardProfile.h \
    src/main/EditorScene.h \
    src/main/Happah.h \
    src/main/MainWindow.h \
    src/main/SplineTool.h \
    src/main/Tool.h \
    src/main/ToolSelector.h \
    src/main/core/geometries/Grid.h \
    src/main/core/SceneManager.h \
    src/main/gui/qt/gl/GlViewport3D.h \
    src/main/core/models/QuadMesh.h \
    src/main/core/geometries/BasicRack.h \
    src/main/core/models/Drawable.h \
    src/main/core/geometries/NonDrawable.h \
    src/main/core/models/TriangleMesh.h \
    src/main/core/DrawManager.h \
    src/main/core/DrawManagerItem.h
SOURCES += src/main/main.cpp \
    src/main/BSplineComponent.cpp \
    src/main/BSplineTool.cpp \
    src/main/Component.cpp \
    src/main/ComponentContainer.cpp \
    src/main/core/geometries/GeometryObject.cpp \
    src/main/core/geometries/SpurGear.cpp \
    src/main/core/geometries/Sphere.cpp \
    src/main/core/geometries/StandardProfile.cpp \
    src/main/EditorScene.cpp \
    src/main/Happah.cpp \
    src/main/MainWindow.cpp \
    src/main/SplineTool.cpp \
    src/main/Tool.cpp \
    src/main/ToolSelector.cpp \
    src/main/core/geometries/Grid.cpp \
    src/main/core/SceneManager.cpp \
    src/main/core/models/QuadMesh.cpp \
    src/main/gui/qt/gl/GlViewport3D.cpp \
    src/main/core/geometries/BasicRack.cpp \
    src/main/core/models/Drawable.cpp \
    src/main/core/geometries/NonDrawable.cpp \
    src/main/core/models/TriangleMesh.cpp \
    src/main/core/DrawManager.cpp \
    src/main/core/DrawManagerItem.cpp
FORMS += 
RESOURCES += 
INCLUDEPATH += /usr/include



