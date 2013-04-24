#ifndef CIRCULARSIMULATIONRESULT_H
#define CIRCULARSIMULATIONRESULT_H

#include <glm/glm.hpp>
#include <math.h>
#include <unordered_map>

#include "happah/HappahTypes.h"


class CircularSimulationResult
{
public:
  CircularSimulationResult(hpuint angleSteps = 100, hpreal startZ = 0.0, hpreal endZ = 0.2, hpuint posZSteps = 30);
  ~CircularSimulationResult();

  void addItem(hpvec3 point);
  hpreal computeAngle(hpvec3 point);
  hpreal computeRadiusXY(hpvec3 point);
  hpuint convertPosZToPosZIdx(hpreal posZ);
  hpreal getItem(hpuint angleSlot, hpuint posZSlot);
  hpreal getItem(hpvec3 point);
  bool isInZRange(hpvec3 point);

private:
  std::unordered_map<hpuint, hpreal>* m_entries;
  hpuint m_angleSteps;
  hpreal m_startZ;
  hpreal m_endZ;
  hpuint m_resolutionZ;
  hpreal m_angleRange;
  hpvec2 m_referenceDir;
};

#endif // CIRCULARSIMULATIONRESULT_H
