#ifndef GEAR_NODE_H
#define GEAR_NODE_H

template<typename G>//extends Gear
class GearNode : SimpleGeometryNode<G> {

public:
	GearNode(G* gear);
	~GearNode();

protected:

};

#endif // GEAR_NODE_H
