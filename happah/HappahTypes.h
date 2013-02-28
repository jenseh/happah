/* Instead of the basic data types the names
 * defined in this file should be used everywhere.
 * This should give us more flexibility as we can
 * change them easily.
 */

#include <glm/glm.hpp>
#include <stdint.h>

//TODO: Types must be replaced where necessary and possible.
typedef glm::mat3x3 hpmat3x3;
typedef glm::mediump_float hpreal;
typedef glm::vec2 hpvec2;
typedef glm::vec3 hpvec3;
typedef glm::vec4 hpvec4;
typedef glm::vec4 hpcolor;



//TODO: What other types should we use?
//Maybe the following for ints?
//typedef int32_t hpint;
//typedef uint32_t hpuint;
