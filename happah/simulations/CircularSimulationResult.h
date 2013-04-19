#ifndef CIRCULARSIMULATIONRESULT_H
#define CIRCULARSIMULATIONRESULT_H

#include <glm/glm.hpp>
#include <math.h>
#include <unordered_map>

#include "happah/HappahTypes.h"


class CircularSimulationResult
{
public:
  CircularSimulationResult(int angleSteps, int posZSteps);

  void addItem(glm::vec3 point, int posZSlot);
  float getItem(int angleSlot, int posZSlot);

private:
  std::unordered_map<int, float>* m_entries;
  int m_angleSteps;
  int m_posZSteps;
  hpreal m_angleRange;
  hpvec3 m_referenceDir;
};

#endif // CIRCULARSIMULATIONRESULT_H
