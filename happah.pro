TEMPLATE = app
TARGET = happah
CONFIG -= release
QT += core \
	gui \
	opengl

#KEEP HEADERS SORTED!!!
HEADERS += \
	happah/Happah.h \
	happah/HappahTypes.h \
	happah/LoggingUtils.h \
	happah/HappahUtils.h\
\
#	happah/geometries/gears/BasicRack.h \
	happah/geometries/BSplineCurve.h \
#	happah/geometries/CircleCloud.h \
#	happah/geometries/ControlNet2.h \
	happah/geometries/DiscGenerator.h \
	happah/geometries/FocalBezierCurve.h \
	happah/geometries/FocalSpline.h \
	happah/geometries/Geometry.h \ 
	happah/geometries/Mesh.h\
	happah/geometries/Plane.h \
	happah/geometries/PointCloud.h\
#	happah/geometries/Sphere.h \
	happah/geometries/SpherePatch.h \
	happah/geometries/gears/StandardProfile.h \
	happah/geometries/SurfaceOfRevolution.h \
#	happah/geometries/TriPatch.h \
	happah/geometries/gears/Worm.h \
	happah/geometries/WormGenerator.h \
	happah/geometries/ZCircleCloud.h \
\
	happah/geometries/gears/CylindricalGear.h \
	happah/geometries/gears/InvoluteGear.h \
	happah/geometries/gears/MatingGearConstructor.h \
	happah/geometries/gears/SimpleGear.h \
	happah/geometries/gears/ToothProfile.h \
\
	happah/gui/DefaultGUIManager.h \
	happah/gui/DiscGearGrindWorker.h \
	happah/gui/DrawManager.h \
	happah/gui/GUIManager.h \
	happah/gui/MainWindow.h \
	happah/gui/SceneGraphExplorerListener.h \
	happah/gui/SceneGraphExplorerPanel.h \
	happah/gui/SimulationTimer.h \
	happah/gui/ToolPanel.h \
	happah/gui/VectorInput.h \ 
	happah/gui/Viewport.h \
	happah/gui/Worker.h \
	happah/gui/WormGearGrindWorker.h \
\
	happah/gui/context-menus/BSplineCurveContextMenu.h \
	happah/gui/context-menus/ContextMenu.h \
	happah/gui/context-menus/DiscContextMenu.h \
	happah/gui/context-menus/InvoluteGearContextMenu.h \
	happah/gui/context-menus/PlaneContextMenu.h \
	happah/gui/context-menus/SimpleGearContextMenu.h \
	happah/gui/context-menus/SimulationContextMenu.h \
	happah/gui/context-menus/ToothProfileContextMenu.h \
	happah/gui/context-menus/TriangleMeshContextMenu.h \
\
	happah/gui/forms/BSplineCurveForm.h \
	happah/gui/forms/DiscForm.h \
	happah/gui/forms/FocalSplineForm.h \
	happah/gui/forms/Form.h \
	happah/gui/forms/InvoluteGearForm.h \
	happah/gui/forms/PlaneForm.h \
	happah/gui/forms/SimpleGearForm.h \
	happah/gui/forms/SimulationForm.h \
	happah/gui/forms/SpherePatchForm.h \
	happah/gui/forms/ToothProfileForm.h \
	happah/gui/forms/WormForm.h \
\
	happah/gui/widgets/FileDialog.h \
	happah/gui/widgets/LabeledIntegerSlider.h \
	happah/gui/widgets/LabeledRealValuedSlider.h \
	happah/gui/widgets/LabeledIntegerSpinBox.h\
\
	happah/kdtree/BBox.h \
	happah/kdtree/BSphere.h \ 
	happah/kdtree/KDTree.h \
	happah/kdtree/KDTreeInnerNode.h \
	happah/kdtree/KDTreeLeaf.h \
	happah/kdtree/KDTreeNode.h \
\
#	happah/math/Circle.h \
	happah/math/Ray.h \
	happah/math/Triangle.h \
	happah/math/Polynom.h \
\
	happah/scene/BSplineCurveNode.h \
	happah/scene/DiscNode.h \
	happah/scene/DrawVisitor.h \
	happah/scene/DiscGearGrindNode.h \
	happah/scene/ElementRenderStateNode.h\
	happah/scene/FocalSplineNode.h \
	happah/scene/GeometryFindVisitor.h \
	happah/scene/GUIStateNode.h \
	happah/scene/InvoluteGearNode.h \
	happah/scene/LineMeshNode.h\
	happah/scene/Material.h \
	happah/scene/Node.h\
	happah/scene/PlaneNode.h \
	happah/scene/PointCloudNode.h\
	happah/scene/PointCloudRenderStateNode.h\
	happah/scene/RayIntersectionVisitor.h \
	happah/scene/RenderStateNode.h\
	happah/scene/SimulationNode.h \
	happah/scene/SimulationVisitor.h \
	happah/scene/SceneListener.h \
	happah/scene/SceneManager.h \
	happah/scene/SceneVisitor.h \
	happah/scene/SimpleGearNode.h \
	happah/scene/SimpleGeometryNode.h \
	happah/scene/SpherePatchNode.h \
	happah/scene/ToothProfileNode.h \
	happah/scene/TriangleMeshNode.h \
	happah/scene/WormGearGrindNode.h \
	happah/scene/WormNode.h \
\
	happah/simulations/CircularSimulationResult.h \
	happah/simulations/DiscGearGrind.h \
	happah/simulations/Kinematic.h \
	happah/simulations/Simulation.h \
	happah/simulations/WormGearGrind.h \
\
	happah/transformations/RigidAffineTransformation.h \
\
	happah/triangulators/RayCloudTriangulator.h \
	happah/triangulators/RayCloudTriangulatorBPA.h \
\
	happah/utilities/GeometryReader.h \
\
	happah-test/benchmarks/KDTreeBenchmark.cpp \
	happah-test/simulations/WormGearGrindTest.h \
	happah-test/tests/CircleTriangleIntersectionTest.h

#KEEP SOURCES SORTED!!!
SOURCES += \
	happah/main.cpp \
	happah/Happah.cpp \
	happah/LoggingUtils.cpp \
	happah/HappahUtils.cpp\
\
#	happah/geometries/gears/BasicRack.cpp \
	happah/geometries/BSplineCurve.cpp \
#	happah/geometries/CircleCloud.cpp \
#	happah/geometries/ControlNet2.cpp \
	happah/geometries/DiscGenerator.cpp \
	happah/geometries/FocalBezierCurve.cpp \
	happah/geometries/FocalSpline.cpp \
	happah/geometries/Geometry.cpp \
	happah/geometries/Mesh.cpp\
	happah/geometries/Plane.cpp \
	happah/geometries/PointCloud.cpp\
#	happah/geometries/Sphere.cpp \
	happah/geometries/SpherePatch.cpp \
	happah/geometries/gears/StandardProfile.cpp \
	happah/geometries/SurfaceOfRevolution.cpp \
#	happah/geometries/TriPatch.cpp \
	happah/geometries/gears/Worm.cpp \
	happah/geometries/WormGenerator.cpp \
	happah/geometries/ZCircleCloud.cpp \
\
	happah/geometries/gears/CylindricalGear.cpp \
	happah/geometries/gears/InvoluteGear.cpp \
	happah/geometries/gears/MatingGearConstructor.cpp \
	happah/geometries/gears/SimpleGear.cpp \
	happah/geometries/gears/ToothProfile.cpp \
\
	happah/gui/DefaultGUIManager.cpp \
	happah/gui/DiscGearGrindWorker.cpp \
	happah/gui/DrawManager.cpp \
	happah/gui/MainWindow.cpp \
	happah/gui/SceneGraphExplorerPanel.cpp \
	happah/gui/SimulationTimer.cpp \
	happah/gui/ToolPanel.cpp \
	happah/gui/VectorInput.cpp \
	happah/gui/Viewport.cpp \
	happah/gui/WormGearGrindWorker.cpp \
\
	happah/gui/context-menus/BSplineCurveContextMenu.cpp \
	happah/gui/context-menus/ContextMenu.cpp \
	happah/gui/context-menus/DiscContextMenu.cpp \
	happah/gui/context-menus/InvoluteGearContextMenu.cpp \
	happah/gui/context-menus/PlaneContextMenu.cpp \
	happah/gui/context-menus/SimpleGearContextMenu.cpp \
	happah/gui/context-menus/SimulationContextMenu.cpp \
	happah/gui/context-menus/ToothProfileContextMenu.cpp \
	happah/gui/context-menus/TriangleMeshContextMenu.cpp \
\
	happah/gui/forms/BSplineCurveForm.cpp \
	happah/gui/forms/DiscForm.cpp \
	happah/gui/forms/FocalSplineForm.cpp \
	happah/gui/forms/Form.cpp \
	happah/gui/forms/InvoluteGearForm.cpp \
	happah/gui/forms/PlaneForm.cpp \
	happah/gui/forms/SimpleGearForm.cpp \
	happah/gui/forms/SimulationForm.cpp \
	happah/gui/forms/SpherePatchForm.cpp \
	happah/gui/forms/ToothProfileForm.cpp \
	happah/gui/forms/WormForm.cpp \
\
	happah/gui/widgets/FileDialog.cpp \
	happah/gui/widgets/LabeledIntegerSlider.cpp \
	happah/gui/widgets/LabeledRealValuedSlider.cpp \
	happah/gui/widgets/LabeledIntegerSpinBox.cpp\
\
	happah/kdtree/BBox.cpp \
	happah/kdtree/BSphere.cpp \
	happah/kdtree/KDTree.cpp \
	happah/kdtree/KDTreeInnerNode.cpp \
	happah/kdtree/KDTreeLeaf.cpp \
	happah/kdtree/KDTreeNode.cpp \
\
	happah/math/Ray.cpp \
\
	happah/scene/BSplineCurveNode.cpp \
	happah/scene/DiscNode.cpp \
	happah/scene/DiscGearGrindNode.cpp \
	happah/scene/ElementRenderStateNode.cpp\
	happah/scene/FocalSplineNode.cpp \
	happah/scene/GUIStateNode.cpp \
	happah/scene/InvoluteGearNode.cpp \
	happah/scene/LineMeshNode.cpp\
	happah/scene/Material.cpp \
	happah/scene/Node.cpp \
	happah/scene/PlaneNode.cpp \
	happah/scene/PointCloudNode.cpp\
	happah/scene/PointCloudRenderStateNode.cpp\
	happah/scene/RayIntersectionVisitor.cpp \
	happah/scene/RenderStateNode.cpp\
	happah/scene/SceneManager.cpp \
	happah/scene/SceneVisitor.cpp \
	happah/scene/SimulationNode.cpp \
	happah/scene/SimpleGearNode.cpp \
	happah/scene/SpherePatchNode.cpp \
	happah/scene/ToothProfileNode.cpp \
	happah/scene/TriangleMeshNode.cpp \
	happah/scene/WormGearGrindNode.cpp \
	happah/scene/WormNode.cpp \
\
	happah/simulations/CircularSimulationResult.cpp \
	happah/simulations/DiscGearGrind.cpp \
	happah/simulations/Kinematic.cpp \
	happah/simulations/Simulation.cpp \
	happah/simulations/WormGearGrind.cpp \
\
	happah/transformations/RigidAffineTransformation.cpp \
\
	happah/triangulators/RayCloudTriangulatorBPA.cpp \
\
	happah/utilities/GeometryReader.cpp \
\	
	happah-test/benchmarks/KDTreeBenchmark.cpp \
	happah-test/simulations/WormGearGrindTest.cpp \
	happah-test/tests/CircleTriangleIntersectionTest.cpp
	
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
