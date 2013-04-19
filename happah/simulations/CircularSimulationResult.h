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

  void addItem(hpvec3 point, hpuint posZSlot);
  hpreal getItem(hpuint angleSlot, hpuint posZSlot);
  hpreal getItem(hpvec3 point, hpuint posZSlot);

private:
  std::unordered_map<hpuint, float>* m_entries;
  hpuint m_angleSteps;
  hpuint m_posZSteps;
  hpreal m_angleRange;
  hpvec3 m_referenceDir;
};

#endif // CIRCULARSIMULATIONRESULT_H
