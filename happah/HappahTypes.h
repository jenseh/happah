#ifndef HP_TYPES_H
#define HP_TYPES_H

#include <glm/glm.hpp>

typedef glm::mat3x3 hpmat3x3;
typedef glm::mat4x4 hpmat4x4;
typedef glm::mediump_float hpreal;
typedef glm::vec2 hpvec2;
typedef glm::vec3 hpvec3;
typedef glm::vec4 hpvec4;
typedef glm::vec4 hpcolor;
typedef unsigned int hpuint;

struct hpcolorRedHash{
	size_t operator()(const hpcolor &color) const{
		return (size_t)color.r*256;  //TODO : find a proper hash;
	}
};

struct hpcolorEqual{
	bool operator()(hpcolor a, hpcolor b) const{
		return a == b;
	}
};

#endif // HP_TYPES_H
