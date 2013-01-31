#ifndef PICKER_H
#define PICKER_H

#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class Picker
{
public:
  Picker();
  bool select(float x,float y,float width,float height,glm::mat4 * toWorld);
};

#endif // PICKER_H
