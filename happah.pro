TEMPLATE = app
TARGET = happah
QT += core \
    gui \
    opengl
HEADERS += src/MainWindow.h \
    src/Happah.h \
    src/Viewport3D.h \
    src/sphere.h
SOURCES += src/MainWindow.cpp \
    src/Happah.cpp \
    src/Viewport3D.cpp \
    src/main.cpp \
    src/sphere.cpp
FORMS += 
RESOURCES += 
INCLUDEPATH += /usr/include
