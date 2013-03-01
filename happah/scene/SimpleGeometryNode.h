#ifndef SIMPLE_GEOMETRY_NODE_H
#define SIMPLE_GEOMETRY_NODE_H

#include <memory>

#include "happah/scene/Node.h"
#include "happah/transformations/RigidAffineTransformation.h"

using namespace std;

template<class G>//extends Geometry
class SimpleGeometryNode : public Node {

public:
	SimpleGeometryNode(shared_ptr<G> geometry)
		: m_geometry(geometry) {}
	virtual ~SimpleGeometryNode() {}

	virtual bool const contains(shared_ptr<void> data) {
		return m_geometry == data;
	}

	virtual void draw(DrawManager& drawManager, RigidAffineTransformation& rigidAffineTransformation) {
		RigidAffineTransformation composedRigidAffineTransformation;
		rigidAffineTransformation.compose(m_rigidAffineTransformation, composedRigidAffineTransformation);
		Node::draw(drawManager, composedRigidAffineTransformation);
	}

	shared_ptr<G> getGeometry() {
		return m_geometry;
	}

protected:
	shared_ptr<G> m_geometry;
	RigidAffineTransformation_ptr m_rigidAffineTransformation;

};
//TODO: upgrade to gcc-4.7 and define:
//template<class G>
//using SimpleGeometryNode_ptr = shared_ptr<SimpleGeometryNode<G> >;

#endif // SIMPLE_GEOMETRY_NODE_H
