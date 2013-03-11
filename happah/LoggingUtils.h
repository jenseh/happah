#ifndef VECTORUTILS_H
#define VECTORUTILS_H

#include <iostream>
#include <string>
#include "glm/glm.hpp"
#include "../../HappahTypes.h"

class VectorUtils
{
public:
  VectorUtils();

  static void printVal(const char* name, hpuint& value);
  static void printVal(const char* name, hpreal& value);
  
  static void printVec(const char* name, glm::vec2& vector);
  static void printVec(const char* name, glm::vec3& vector);
  static void printVec(const char* name, glm::vec4& vector);
  
  static void printVec(glm::vec2& vector);
  static void printVec(glm::vec3& vector);
  static void printVec(glm::vec4& vector);
};

#endif // VECTORUTILS_H
