/*
 * GeomtryObject.h
 *
 *  Created on: Nov 28, 2012
 *      Author: matthias
 */

#ifndef GEOMETRYOBJECT_H_
#define GEOMETRYOBJECT_H_

#include <glm/glm.hpp>

using glm::vec4;
using glm::vec3;

class GeometryObject {
public:
	GeometryObject(vec4 position);
	virtual ~GeometryObject();
private:
	vec4 position_;
};

#endif /* GEOMETRYOBJECT_H_ */
