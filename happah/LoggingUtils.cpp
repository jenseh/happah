#include "LoggingUtils.h"

LoggingUtils::LoggingUtils()
{
}

void LoggingUtils::printVal(const char* name, hpuint& value) {
  std::cout << name << ": " << value << std::endl;
}

void LoggingUtils::printVal(const char* name, hpreal& value) {
  std::cout << name << ": " << value << std::endl;
}

void LoggingUtils::printVec(const char* name, glm::vec2& vector) {
  std::cout << name << ": ";
  printVec(vector);
}

void LoggingUtils::printVec(const char* name, glm::vec3& vector) {
  std::cout << name << ": ";
  printVec(vector);
}

void LoggingUtils::printVec(const char* name, glm::vec4& vector) {
  std::cout << name << ": ";
  printVec(vector);
}

void LoggingUtils::printVec(glm::vec2& vector) {
  std::cout << "[" << vector.x << ", " << vector.y << "]" << std::endl;
}
void LoggingUtils::printVec(glm::vec3& vector) {
  std::cout << "[" << vector.x << ", " << vector.y << ", " << vector.z << "]" <<  std::endl;
}
void LoggingUtils::printVec(glm::vec4& vector) {
  std::cout << "[" << vector.x << ", " << vector.y << ", " << vector.z << ", " << vector.w << "]" << std::endl;
}
