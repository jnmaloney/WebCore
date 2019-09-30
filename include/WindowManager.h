#pragma once


#include "graphics.h"


class WindowManager
{
public:

  WindowManager();
  ~WindowManager();

  static WindowManager* getInstance() { return s_currentInstance; }

  int init(const char* title);

  GLFWwindow* g_window;
  int width = 200; //800;
  int height = 480; //600;

  float mousex = 0.f;
  float mousey = 0.f;

  glm::vec4 getViewport();

protected:

  static WindowManager* s_currentInstance;

};
