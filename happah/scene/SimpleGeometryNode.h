#ifndef SIMPLE_GEOMETRY_NODE_H
#define SIMPLE_GEOMETRY_NODE_H

template<typename G>//extends Geometry
class SimpleGeometryNode : public Node {

public:
	SimpleGeometryNode(G* geometry);
	~SimpleGeometryNode();

	G* getGeometry();

protected:
	G* m_geometry;

};

#endif // SIMPLE_GEOMETRY_NODE_H
