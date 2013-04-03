#include "LoggingUtils.h"

LoggingUtils::LoggingUtils()
{
}

void LoggingUtils::printVal(const char* name, hpuint& value) {
  cout << name << ": " << value << std::endl;
}

void LoggingUtils::printVal(const char* name, hpreal& value) {
  cout << name << ": " << value << std::endl;
}

void LoggingUtils::printVec(const char* name, glm::vec2& vector) {
  cout << name << ": ";
  printVec(vector);
}

void LoggingUtils::printVec(const char* name, glm::vec3& vector) {
  cout << name << ": ";
  printVec(vector);
}

void LoggingUtils::printVec(const char* name, glm::vec4& vector) {
  cout << name << ": ";
  printVec(vector);
}

void LoggingUtils::printVec(glm::vec2& vector) {
  cout << "[" << vector.x << ", " << vector.y << "]" << std::endl;
}
void LoggingUtils::printVec(glm::vec3& vector) {
  cout << "[" << vector.x << ", " << vector.y << ", " << vector.z << "]" <<  std::endl;
}
void LoggingUtils::printVec(glm::vec4& vector) {
  cout << "[" << vector.x << ", " << vector.y << ", " << vector.z << ", " << vector.w << "]" << std::endl;
}

void LoggingUtils::print(InvoluteGear& involuteGear) {
  cout << "InvoluteGear:" << endl;
  cout << "number of teeth  = " << involuteGear.getNumberOfTeeth() << endl;
  cout << "module           = " << involuteGear.getModule() << endl;
  cout << "pressure angle   = " << involuteGear.getPressureAngle() << endl;
  cout << "tip radius       = " << involuteGear.getTipRadius() << endl;
  cout << "ref. radius      = " << involuteGear.getReferenceRadius() << endl;
  cout << "base radius      = " << involuteGear.getBaseRadius() << endl;
  cout << "root radius      = " << involuteGear.getRootRadius() << endl;
  cout << "fillet radius    = " << involuteGear.getFilletRadius() << endl;
  cout << "bottom clearance = " << involuteGear.getBottomClearance() << endl;
  cout << "helix angle      = " << involuteGear.getHelixAngle() << endl;
  cout << "angular pitch    = " << involuteGear.getAngularPitch() << endl;
}

void LoggingUtils::print(SimpleGear& simpleGear) {
  cout << "SimpleGear:" << endl;
  cout << "helix angle = " << simpleGear.getHelixAngle() << endl;
  cout << "face width  = " << simpleGear.getFacewidth() << endl;
  cout << "controlpoints: " << endl;
  BSplineCurve toothProfile = simpleGear.getToothProfile();
  for(hpuint i = 0; i < toothProfile.getNumberOfControlPoints(); ++i) {
    hpvec3 point = toothProfile.getControlPoint(i);
    LoggingUtils::printVec(point);
  }
  cout << endl;
}