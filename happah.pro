TEMPLATE = app
TARGET = happah
QT += core \
    gui \
    opengl
HEADERS += src/main/BSplineComponent.h \
    src/main/BSplineTool.h \
    src/main/Component.h \
    src/main/ComponentContainer.h \
    src/main/EditorScene.h \
    src/main/qt/qgl/QglGear.h \
    src/main/qt/qgl/QglGeometryObject.h \
    src/main/qt/qgl/QglGrid.h \
    src/main/Happah.h \
    src/main/MainWindow.h \
    src/main/SplineTool.h \
    src/main/Tool.h \
    src/main/ToolSelector.h \
    src/main/qt/qgl/QglViewport3D.h \
    src/main/qt/qgl/QglSphere.h \
    src/main/StandardProfile.h \
    src/main/core/GeometryObject.h
SOURCES += src/main/main.cpp \
    src/main/BSplineComponent.cpp \
    src/main/BSplineTool.cpp \
    src/main/Component.cpp \
    src/main/ComponentContainer.cpp \
    src/main/EditorScene.cpp \
    src/main/qt/qgl/QglGear.cpp \
    src/main/qt/qgl/QglGeometryObject.cpp \
    src/main/qt/qgl/QglGrid.cpp \
    src/main/Happah.cpp \
    src/main/MainWindow.cpp \
    src/main/SplineTool.cpp \
    src/main/Tool.cpp \
    src/main/ToolSelector.cpp \
    src/main/qt/qgl/QglViewport3D.cpp \
    src/main/qt/qgl/QglSphere.cpp \
    src/main/StandardProfile.cpp \
    src/main/core/GeometryObject.cpp
FORMS += 
RESOURCES += 
INCLUDEPATH += /usr/include

