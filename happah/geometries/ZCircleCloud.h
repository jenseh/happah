#ifndef ZCIRCLECLOUD_H
#define ZCIRCLECLOUD_H

#include <vector>

#include "happah/math/Circle.h"
#include "happah/HappahTypes.h"

/**
 * @class ZCircleCloud
 * @brief Set/cloud of circles oriented along the Z axis and lying in the XY plane.
 * The set is evenly spaced and specified by its start end end Z value and
 * the number of circles in between (resolutionZ). All circles have the same
 * radius (maxRadius) and can be extracted by using computeOuterCircle(..).
 */
class ZCircleCloud {
public:
	/**
	 * @brief ZCircleCloud default constructor for specifying a CircleCloud.
	 * @param maxradius The actual radius of each circle which should be equal
	 *  to the maximum radius of the represented object.
	 * @param startZ The z value where our ZCircleCloud starts.
	 * @param endZ The z value where our ZCircleCloud ends.
	 * @param resolutionZ The number of circles.
	 */
	ZCircleCloud(hpreal maxRadius, hpreal startZ, hpreal endZ, hpuint posZSteps);

	/**
	 * @brief Compute the outermost circle given the current z slot.
	 * @param The index of the current Z slot with regard to startZ, endZ and resolutionZ.
	 * @return A new circle object with at the corresponding Z value with normal oriented along the Z axis.
	 */
	Circle computeOuterCircle(hpuint posZSlot);

	/**
	 * @brief Get the maxRadius value which is the radius of each circle in this cloud.
	 * @return The circle radius.
	 */
	hpreal getMaxRadius();

	/**
	 * @brief Get the resolutionZ value which represents the number of circles.
	 * @return The number of circles.
	 */
	hpuint getPosZSteps();

private:
	hpreal m_maxRadius;

	hpreal m_startZ;
	hpreal m_endZ;
	hpuint m_resolutionZ;

	hpreal convertPosZSlotToPosZ(hpuint posZSlot);
};

typedef std::shared_ptr<ZCircleCloud> ZCircleCloud_ptr;

#endif // ZCIRCLECLOUD_H
