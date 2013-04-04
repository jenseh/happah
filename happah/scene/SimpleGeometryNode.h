#ifndef SIMPLE_GEOMETRY_NODE_H
#define SIMPLE_GEOMETRY_NODE_H

#include "happah/scene/Node.h"
#include "happah/transformations/RigidAffineTransformation.h"
#include "happah/scene/SelectListener.h"

template<class G>//extends Geometry
class SimpleGeometryNode : public Node {

public:
	SimpleGeometryNode(shared_ptr<G> geometry)
		: m_geometry(geometry),m_selectListener(*this) {}

	SimpleGeometryNode(shared_ptr<G> geometry, RigidAffineTransformation& transformation)
		: m_geometry(geometry), m_rigidAffineTransformation(transformation),m_selectListener(*this) {}

	virtual ~SimpleGeometryNode() {}

	virtual bool contains(shared_ptr<void> data) const {
		return m_geometry == data;
	}

	virtual void draw(DrawVisitor& drawVisitor, RigidAffineTransformation& rigidAffineTransformation) {
		RigidAffineTransformation composedRigidAffineTransformation;
		rigidAffineTransformation.compose(m_rigidAffineTransformation, composedRigidAffineTransformation);
		Node::draw(drawVisitor, composedRigidAffineTransformation);
	}

	shared_ptr<G> getGeometry() {
		return m_geometry;
	}

	class DefaultSelectListener : public SelectListener {


		public:
			DefaultSelectListener(SimpleGeometryNode& simpleGeometryNode)
			: m_simpleGeometryNode(simpleGeometryNode){}
			~DefaultSelectListener(){}

			void handleSelectEvent(){}
			void handleDeselectEvent(){}

		private:
			SimpleGeometryNode& m_simpleGeometryNode;
		};

	virtual DefaultSelectListener* getSelectListener() {
		return &m_selectListener;
	}
protected:
	shared_ptr<G> m_geometry;
	RigidAffineTransformation m_rigidAffineTransformation;
	DefaultSelectListener m_selectListener;
};
//TODO: upgrade to gcc-4.7 and define:
//template<class G>
//using SimpleGeometryNode_ptr = shared_ptr<SimpleGeometryNode<G> >;

#endif // SIMPLE_GEOMETRY_NODE_H
