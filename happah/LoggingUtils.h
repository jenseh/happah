#ifndef LOGGINGUTILS_H
#define LOGGINGUTILS_H

#include <iostream>
#include <ostream>
#include <string>

using namespace std;

#include "glm/glm.hpp"
#include "happah/geometries/gears/InvoluteGear.h"
#include "happah/geometries/gears/SimpleGear.h"
#include "happah/math/Circle.h"
#include "happah/HappahTypes.h"

class LoggingUtils
{
public:
	LoggingUtils();

	static void printVal(const char* name, hpuint value);
	static void printVal(const char* name, hpreal value);
	static void printVal(const char* name, bool& value);

	static void printVec(const char* name, hpvec2& vector);
	static void printVec(const char* name, hpvec3& vector);
	static void printVec(const char* name, hpvec4& vector);

	static void printVec(hpvec2& vector);
	static void printVec(hpvec3& vector);
	static void printVec(hpvec4& vector);

	static void print(InvoluteGear& involuteGear);
	static void print(SimpleGear& simpleGear);

	static void print(const char* name, Triangle& triangle);
	static void print(const char* name, Circle& circle);
	static void print(Circle& circle);
};

#endif // LOGGINGUTILS_H
