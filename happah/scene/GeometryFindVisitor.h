#ifndef DISCFINDVISITOR_H_
#define DISCFINDVISITOR_H_
#include "happah/scene/SceneVisitor.h"
#include "happah/scene/DiscNode.h"
#include "happah/scene/InvoluteGearNode.h"
#include "happah/scene/PlaneNode.h"
#include "happah/scene/SimpleGearNode.h"
#include "happah/scene/SpherePatchNode.h"
#include "happah/scene/WormNode.h"



class GeometryFindVisitor: public SceneVisitor {

	vector<InvoluteGear_ptr > involuteGears;
	vector<Plane_ptr> planes;
	vector<SimpleGear_ptr> simpleGears;
	vector<SurfaceOfRevolution_ptr> discs;
	vector<Worm_ptr> worms;
	vector<SpherePatch_ptr> spherePatches;

	vector<SurfaceOfRevolution_ptr> getDiscs(){
		return discs;
	}
	vector<SimpleGear_ptr> getSimpleGears() {
		return simpleGears;
	}

	void visit(InvoluteGearNode& involuteGearNode) {
		involuteGears.push_back(involuteGearNode.getGeometry());
	}

	void visit(PlaneNode& planeNode) {
		planes.push_back(planeNode.getGeometry());
	}

	void visit(TriangleMeshNode& triangleMeshNode) {}

	void visit(LineMeshNode& lineMeshNode) {}

	void visit(PointCloudNode& pointCloudNode) {}

	void visit(RenderStateNode& renderStateNode) {}

	void visit(ElementRenderStateNode& elementRenderStateNode) {}

	void visit(SimpleGearNode& simpleGearNode) {
		simpleGears.push_back(simpleGearNode.getGeometry());
	}

	void visit(DiscNode& discNode) {
		discs.push_back(discNode.getGeometry());
	}

	void visit(WormNode& wormNode) {
		worms.push_back(wormNode.getGeometry());
	}

	void visit(SpherePatchNode& spherePatchNode) {
		spherePatches.push_back(spherePatchNode.getGeometry());
	}
};
#endif /* DISCFINDVISITOR_H_ */
