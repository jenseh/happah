TEMPLATE = app
TARGET = happah
QT += core \
    gui \
    opengl
HEADERS += src/BSplineComponent.h \
    src/BSplineTool.h \
    src/Component.h \
    src/ComponentContainer.h \
    src/EditorScene.h \
    src/Gear.h \
    src/GeometryObject.h \
    src/Grid.h \
    src/Happah.h \
    src/main.h \
    src/MainWindow.h \
    src/SplineTool.h \
    src/Tool.h \
    src/ToolSelector.h \
    src/Viewport3D.h \
    src/Sphere.h
SOURCES += src/BSplineComponent.cpp \
    src/BSplineTool.cpp \
    src/Component.cpp \
    src/ComponentContainer.cpp \
    src/EditorScene.cpp \
    src/Gear.cpp \
    src/GeometryObject.cpp \
    src/Grid.cpp \
    src/Happah.cpp \
    src/main.cpp \
    src/MainWindow.cpp \
    src/SplineTool.cpp \
    src/Tool.cpp \
    src/ToolSelector.cpp \
    src/Viewport3D.cpp \
    src/Sphere.cpp
FORMS += 
RESOURCES +=
INCLUDEPATH += /usr/include
OTHER_FILES +=
