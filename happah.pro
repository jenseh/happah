TEMPLATE = app
TARGET = happah
CONFIG -= release
QT += core \
	gui \
	opengl

HEADERS += happah/*.h happah/geometries/*.h happah/geometries/gears/*.h happah/geometries/gears/matinggear/*.h happah/gui/*.h happah/gui/context-menus/*.h happah/gui/forms/*.h happah/gui/widgets/*.h happah/io/*.h happah/kdtree/*.h happah/math/*.h happah/scene/*.h happah/simulations/*.h happah/transformations/*.h happah/triangulators/*.h \
    happah/kdtree/FastKdTree.h

SOURCES += happah/*.cpp happah/geometries/*.cpp happah/geometries/gears/*.cpp happah/geometries/gears/matinggear/*.cpp happah/gui/*.cpp happah/gui/context-menus/*.cpp happah/gui/forms/*.cpp happah/gui/widgets/*.cpp happah/io/*.cpp happah/kdtree/*.cpp happah/math/*.cpp happah/scene/*.cpp happah/simulations/*.cpp happah/transformations/*.cpp happah/triangulators/*.cpp
	
FORMS += 
RESOURCES += 

win32 {
	QMAKE_CXXFLAGS += -std=c++0x -U__STRICT_ANSI__ -DGL_GLEXT_PROTOTYPES
	LIBS += -lglew32
	INCLUDEPATH += ./
}

unix {
	QMAKE_CXXFLAGS += -std=c++0x -Wno-unused-variable -Wno-unused-parameter
	LIBS += -lGLEW
        INCLUDEPATH += /usr/include $$system(pwd)\
}

CONFIG(debug) {
	DESTDIR = build/debug
}

CONFIG(release) {
	DESTDIR = build/release
}

OBJECTS_DIR = $$DESTDIR/.obj
MOC_DIR = $$DESTDIR/.moc
RCC_DIR = $$DESTDIR/.rrc
UI_DIR = $$DESTDIR/.ui
