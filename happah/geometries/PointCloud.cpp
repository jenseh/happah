#include "happah/geometries/PointCloud.h"

PointCloud::PointCloud(vector<hpvec2>* vertices) {
	m_vertices = new vector<hpvec3>(vertices->size());
	vector<hpvec3>::iterator itVec3 = m_vertices->begin();
	for(vector<hpvec2>::iterator it = vertices->begin(), end = vertices->end(); it != end; ++it) {
		(*itVec3) = hpvec3(*it, 0.0f);
		++itVec3;
	}
	delete vertices;
}

PointCloud::PointCloud(vector<hpvec3>* vertices)
	:m_vertices(vertices){}

PointCloud::~PointCloud(){
	delete m_vertices;
}

vector<hpvec3>* PointCloud::getVertices(){
	return m_vertices;
}
