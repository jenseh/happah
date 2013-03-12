#ifndef POINT_CLOUD_H_
#define POINT_CLOUD_H_

#include <glm/glm.hpp>
#include <memory>
#include <vector>
#include "happah/HappahTypes.h"
using namespace std;

class PointCloud{
public:
	PointCloud(vector<hpvec3>* vertices);
	virtual ~PointCloud();

	vector<hpvec3>*getVertices();

private:
	vector<hpvec3>* m_vertices;

};
typedef shared_ptr<PointCloud> PointCloud_ptr;

#endif //POINT_CLOUD_H_
