#pragma once


#include "graphics.h"
#include <vector>


class Palette
{
public:
  Palette() {}
  ~Palette() {}

  glm::vec3& getAt(int i)
  {
      return colours[i % colours.size()];
  }

  std::vector<glm::vec3> colours;
};
