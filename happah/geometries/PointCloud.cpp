#include "happah/geometries/PointCloud.h"

PointCloud::PointCloud(vector<hpvec3>* vertices)
	:m_vertices(vertices){}

PointCloud::~PointCloud(){
	delete m_vertices;
}

vector<hpvec3>* PointCloud::getVertices(){
	return m_vertices;
}
