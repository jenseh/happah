#ifndef LOGGINGUTILS_H
#define LOGGINGUTILS_H

#include <iostream>
#include <string>
#include "glm/glm.hpp"
#include "happah/HappahTypes.h"

class LoggingUtils
{
public:
	LoggingUtils();

  static void printVal(const char* name, hpuint& value);
  static void printVal(const char* name, hpreal& value);
  
  static void printVec(const char* name, glm::vec2& vector);
  static void printVec(const char* name, glm::vec3& vector);
  static void printVec(const char* name, glm::vec4& vector);
  
  static void printVec(glm::vec2& vector);
  static void printVec(glm::vec3& vector);
  static void printVec(glm::vec4& vector);
};

#endif // LOGGINGUTILS_H
