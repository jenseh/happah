#include "LoggingUtils.h"

LoggingUtils::LoggingUtils()
{
}

void LoggingUtils::printVal(const char* name, hpuint value) {
  cout << name << ": " << value << std::endl;
}

void LoggingUtils::printVal(const char* name, hpreal value) {
  cout << name << ": " << value << std::endl;
}

void LoggingUtils::printVal(const char* name, bool& value) {
  cout << name << ": " << value << std::endl;
}


void LoggingUtils::printVec(const char* name, hpvec2& vector) {
  cout << name << ": ";
  printVec(vector);
}

void LoggingUtils::printVec(const char* name, hpvec3& vector) {
  cout << name << ": ";
  printVec(vector);
}

void LoggingUtils::printVec(const char* name, hpvec4& vector) {
  cout << name << ": ";
  printVec(vector);
}

void LoggingUtils::printVec(hpvec2& vector) {
  cout << "[" << vector.x << ", " << vector.y << "]" << std::endl;
}
void LoggingUtils::printVec(hpvec3& vector) {
  cout << "[" << vector.x << ", " << vector.y << ", " << vector.z << "]" <<  std::endl;
}
void LoggingUtils::printVec(hpvec4& vector) {
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
  cout << "face width  = " << simpleGear.getFaceWidth() << endl;
  cout << "controlpoints: " << endl;
  BSplineCurve<hpvec3> toothProfile = simpleGear.getToothProfile().getCurve();
  for(hpuint i = 0; i < toothProfile.getNumberOfControlPoints(); ++i) {
    hpvec3 point = toothProfile.getControlPoint(i);
    LoggingUtils::printVec(point);
  }
  cout << endl;
}

//void LoggingUtils::print(Circle& circle) {
//	cout << "Circle: " << endl;
//	LoggingUtils::printVec("center", circle.m_center);
//	LoggingUtils::printVec("normal", circle.m_normal);
//	LoggingUtils::printVal("radius", circle.m_radius);
//}
