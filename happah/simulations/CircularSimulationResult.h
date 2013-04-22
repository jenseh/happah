#ifndef CIRCULARSIMULATIONRESULT_H
#define CIRCULARSIMULATIONRESULT_H

#include <glm/glm.hpp>
#include <math.h>
#include <unordered_map>

#include "happah/HappahTypes.h"


class CircularSimulationResult
{
public:
  CircularSimulationResult(hpuint angleSteps = 100, hpuint posZSteps = 30);
  ~CircularSimulationResult();

  void addItem(hpvec3 point, hpuint posZSlot);
  hpreal computeAngle(hpvec3 point);
  hpreal getItem(hpuint angleSlot, hpuint posZSlot);
  hpreal getItem(hpvec3 point, hpuint posZSlot);

private:
  std::unordered_map<hpuint, hpreal>* m_entries;
  hpuint m_angleSteps;
  hpuint m_resolutionZ;
  hpreal m_angleRange;
  hpvec2 m_referenceDir;
};

#endif // CIRCULARSIMULATIONRESULT_H
