TEMPLATE = app
TARGET = happah
QT += core \
    gui \
    opengl
HEADERS += src/MainWindow.h \
    src/Happah.h \
    src/Viewport3D.h \
    src/sphere.h \
    src/GeometryObject.h \
    src/Gear.h
SOURCES += src/MainWindow.cpp \
    src/Happah.cpp \
    src/Viewport3D.cpp \
    src/main.cpp \
    src/sphere.cpp \
    src/GeometryObject.cpp \
    src/Gear.cpp
FORMS += 
RESOURCES +=
INCLUDEPATH += /usr/include
OTHER_FILES +=
