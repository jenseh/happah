#include "VectorUtils.h"

VectorUtils::VectorUtils()
{
}

void VectorUtils::printVal(const char* name, hpuint& value) {
  std::cout << name << ": " << value << std::endl;
}

void VectorUtils::printVal(const char* name, hpreal& value) {
  std::cout << name << ": " << value << std::endl;
}

void VectorUtils::printVec(const char* name, glm::vec2& vector) {
  std::cout << name << ": ";
  printVec(vector);
}

void VectorUtils::printVec(const char* name, glm::vec3& vector) {
  std::cout << name << ": ";
  printVec(vector);
}

void VectorUtils::printVec(const char* name, glm::vec4& vector) {
  std::cout << name << ": ";
  printVec(vector);
}

void VectorUtils::printVec(glm::vec2& vector) {
  std::cout << "[" << vector.x << ", " << vector.y << "]" << std::endl;
}
void VectorUtils::printVec(glm::vec3& vector) {
  std::cout << "[" << vector.x << ", " << vector.y << ", " << vector.z << "]" <<  std::endl;
}
void VectorUtils::printVec(glm::vec4& vector) {
  std::cout << "[" << vector.x << ", " << vector.y << ", " << vector.z << ", " << vector.w << "]" << std::endl;
}
