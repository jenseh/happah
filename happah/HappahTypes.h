#ifndef HP_TYPES_H
#define HP_TYPES_H

#include <glm/glm.hpp>
#include <memory>
#include <vector>
typedef glm::mat3x3 hpmat3x3;
typedef glm::mat4x4 hpmat4x4;
typedef glm::mediump_float hpreal;
typedef glm::vec2 hpvec2;
typedef glm::vec3 hpvec3;
typedef glm::vec4 hpvec4;
typedef glm::vec4 hpcolor;
typedef unsigned int hpuint;

class ElementRenderStateNode;
typedef std::shared_ptr<ElementRenderStateNode> ElementRenderStateNode_ptr;
class PointCloudRenderStateNode;
typedef std::shared_ptr<PointCloudRenderStateNode> PointCloudRenderStateNode_ptr;

#endif // HP_TYPES_H
