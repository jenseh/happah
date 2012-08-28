TEMPLATE = app
TARGET = happah
QT += core \
    gui \
    opengl
HEADERS += src/menu.h \
    src/render.h
SOURCES += src/menu.cpp \
    src/render.cpp \
    src/main.cpp
FORMS += 
RESOURCES += 

INCLUDEPATH += /usr/include