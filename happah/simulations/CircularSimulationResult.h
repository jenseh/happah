#ifndef CIRCULARSIMULATIONRESULT_H
#define CIRCULARSIMULATIONRESULT_H

#include <ext/hash_map>
#include <glm/glm.hpp>
#include <math.h>

#include "happah/HappahTypes.h"

using namespace __gnu_cxx;

class CircularSimulationResult
{
public:
  CircularSimulationResult(int angleSteps, int posZSteps);

  void addItem(glm::vec3 point, int posZSlot);
  float getItem(int angleSlot, int posZSlot);

private:
  hash_map<int, float>* m_entries;
  int m_angleSteps;
  int m_posZSteps;
  hpreal m_angleRange;
  hpvec3 m_referenceDir;
};

#endif // CIRCULARSIMULATIONRESULT_H
