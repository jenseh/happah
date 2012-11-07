
TEMPLATE = app
TARGET = happah

QT += core \
    gui \
    opengl
HEADERS += src/MainWindow.h \
    src/Happah.h \
    src/Viewport3D.h \
    src/sphere.h \
    src/GeometryObject.h
SOURCES += src/MainWindow.cpp \
    src/Happah.cpp \
    src/Viewport3D.cpp \
    src/main.cpp \
    src/sphere.cpp \
    src/GeometryObject.cpp
FORMS += 
RESOURCES += Resources.qrc \
    Resources.qrc
INCLUDEPATH += /usr/include
OTHER_FILES += src/shader/phongFrag.glsl \
    src/shader/phongVert.glsl \
    src/shader/simpleFrag.glsl \
    src/shader/simpleVert.glsl

