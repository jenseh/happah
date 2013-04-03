#ifndef LOGGINGUTILS_H
#define LOGGINGUTILS_H

#include <iostream>
#include <ostream>
#include <string>

using namespace std;

#include "glm/glm.hpp"
#include "happah/geometries/gears/InvoluteGear.h"
#include "happah/geometries/gears/SimpleGear.h"
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

	static void print(InvoluteGear& involuteGear);
	static void print(SimpleGear& simpleGear);
};

#endif // LOGGINGUTILS_H
