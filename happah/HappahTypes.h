#ifndef HP_TYPES_H
#define HP_TYPES_H

#include <glm/glm.hpp>
#include <memory>
#include <vector>
#include <cmath>

typedef glm::mat2x2 hpmat2x2;
typedef glm::mat3x3 hpmat3x3;
typedef glm::mat4x4 hpmat4x4;
typedef glm::mediump_float hpreal;
typedef double hpdouble;
typedef glm::vec2 hpvec2;
typedef glm::vec3 hpvec3;
typedef glm::vec4 hpvec4;
typedef glm::vec4 hpcolor;
typedef unsigned int hpuint;

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
typedef unsigned int uint;
#endif

#if defined(MSVC2012)	
#define constexpr const
#define INFINITY _FPCLASS_PINF

#define isnan(x) _isnan(x)
#define isinf(x) !_finite(x)
#define round(x) (floor((x)+0.5))

#else
#define isnan(x) std::isnan(x)
#define isinf(x) std::isinf(x)
#endif  
typedef std::vector<hpvec2> PointCloud2D;
typedef std::vector<hpvec3> RayCloud3D;

class ElementRenderStateNode;
typedef std::shared_ptr<ElementRenderStateNode> ElementRenderStateNode_ptr;
class PointCloudRenderStateNode;
typedef std::shared_ptr<PointCloudRenderStateNode> PointCloudRenderStateNode_ptr;
#endif // HP_TYPES_H
