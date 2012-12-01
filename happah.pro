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
    src/main/core/geometries/Gear.h \
    src/main/core/geometries/Sphere.h \
    src/main/core/geometries/StandardProfile.h \
    src/main/EditorScene.h \
    src/main/gui/qt/qgl/QglGear.h \
    src/main/gui/qt/qgl/QglGeometryObject.h \
    src/main/gui/qt/qgl/QglGrid.h \
    src/main/gui/qt/qgl/QglSphere.h \
    src/main/gui/qt/qgl/QglViewport3D.h \
    src/main/Happah.h \
    src/main/MainWindow.h \
    src/main/SplineTool.h \
    src/main/Tool.h \
    src/main/ToolSelector.h \
    src/main/core/geometries/Grid.h
SOURCES += src/main/main.cpp \
    src/main/BSplineComponent.cpp \
    src/main/BSplineTool.cpp \
    src/main/Component.cpp \
    src/main/ComponentContainer.cpp \
    src/main/core/geometries/GeometryObject.cpp \
    src/main/core/geometries/Gear.cpp \
    src/main/core/geometries/Sphere.cpp \
    src/main/core/geometries/StandardProfile.cpp \
    src/main/EditorScene.cpp \
    src/main/gui/qt/qgl/QglGear.cpp \
    src/main/gui/qt/qgl/QglGeometryObject.cpp \
    src/main/gui/qt/qgl/QglGrid.cpp \
    src/main/gui/qt/qgl/QglSphere.cpp \
    src/main/gui/qt/qgl/QglViewport3D.cpp \
    src/main/Happah.cpp \
    src/main/MainWindow.cpp \
    src/main/SplineTool.cpp \
    src/main/Tool.cpp \
    src/main/ToolSelector.cpp \
    src/main/core/geometries/Grid.cpp
FORMS += 
RESOURCES += 
INCLUDEPATH += /usr/include

