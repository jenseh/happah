#ifndef CIRCULARSIMULATIONRESULT_H
#define CIRCULARSIMULATIONRESULT_H

#include <math.h>
#include <ext/hash_map>
#include <glm/glm.hpp>

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
  float m_angleRange;
  glm::vec3 referenceDir;
};

#endif // CIRCULARSIMULATIONRESULT_H
