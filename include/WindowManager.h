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
  int width = 800;
  int height = 600;

protected:

  static WindowManager* s_currentInstance;

};
