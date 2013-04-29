#ifndef CIRCULARSIMULATIONRESULT_H
#define CIRCULARSIMULATIONRESULT_H

#include <glm/glm.hpp>
#include <math.h>
#include <unordered_map>

#include "happah/HappahTypes.h"

/**
 * @class CircularSimulationResult
 *
 * @brief This class manages a hashmap holding the results of a simulation computation.
 * It can only be used if we know that our results lie on a cylindrical object
 * where the cyclical part lies in the XY plane and the axis of rotation is
 * equivalent to the Z axis.
 */
class CircularSimulationResult
{
public:
	/**
	 * @brief
	 * @param angleSteps
	 * @param startZ
	 * @param endZ
	 * @param
	 */
	CircularSimulationResult(hpuint angleSteps = 100, hpreal startZ = 0.0, hpreal endZ = 0.2, hpuint posZSteps = 30);
	~CircularSimulationResult();

  bool addItem(hpvec3 point);
  hpreal computeAngle(hpvec3 point);
  hpuint computeAngleSlot(hpreal angle);
  hpreal computeRadiusXY(hpvec3 point);
  hpuint computeSlot(hpuint angleSlot, hpuint posZSlot);
  hpuint convertPosZToPosZSlot(hpreal posZ);
  hpreal getItem(hpuint angleSlot, hpuint posZSlot);
  hpreal getItem(hpvec3 point);
  hpuint getPosZSteps();
  bool isInZRange(hpvec3 point);

private:
  std::unordered_map<hpuint, hpreal>* m_entries;
  hpuint m_angleSteps;

  hpreal m_startZ;
  hpreal m_endZ;
  hpuint m_posZSteps;
  hpreal m_angleRange;
};

#endif // CIRCULARSIMULATIONRESULT_H
