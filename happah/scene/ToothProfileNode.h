#ifndef TOOTHPROFILENODE_H
#define TOOTHPROFILENODE_H

#include <memory>

#include "happah/geometries/gears/ToothProfile.h"
#include "happah/scene/GUIStateNode.h"
#include "happah/scene/LineMeshNode.h"
#include "happah/scene/PointCloudNode.h"
#include "happah/scene/SceneVisitor.h"
#include "happah/scene/SimpleGeometryNode.h"

class ToothProfileNode : public SimpleGeometryNode<ToothProfile> {
public:
	ToothProfileNode(ToothProfile_ptr toothProfile);
	~ToothProfileNode();

	void accept(SceneVisitor& sceneVisitor);
	void insertChild(ToothProfileGUIStateNode_ptr toothProfileGUIStateNode);
	void insertChild(PointCloudNode_ptr pointCloudNode);
	void insertChild(LineMeshNode_ptr lineMeshNode);
};

typedef std::shared_ptr<ToothProfileNode> ToothProfileNode_ptr;

#endif //TOOTHPROFILENODE_H