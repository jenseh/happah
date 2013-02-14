/* Instead of the basic data types the names
 * defined in this file should be used everywhere.
 * This should give us more flexibility as we can
 * change them easily.
 */
#include <stdint.h>
#include "glm/glm.hpp"

//TODO: Types must be replaced where necessary and possible.
typedef glm::mediump_float hpreal;
typedef glm::vec2 hpvec2;
typedef glm::vec3 hpvec3;
typedef glm::vec4 hpvec4;

typedef glm::mat3x3 hp3x3;
//TODO: What other types should we use?
//Maybe the following for ints?
//typedef int32_t hpint;
//typedef uint32_t hpuint;