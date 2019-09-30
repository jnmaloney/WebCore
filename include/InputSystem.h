#pragma once


#include "WindowManager.h"


class InputSystem
{
public:
  InputSystem(WindowManager& window);
  ~InputSystem();

  void cursor_pos_callback(double xpos, double ypos);
  void mouse_button_callback(int button, int action, int mods);
  void key_callback(int key, int scancode, int action, int mods);
  void char_callback(unsigned int button);

  bool captureMouse();

  void frame();
  double m_cursor_x = 0.0;
  double m_cursor_y = 0.0;

protected:

  WindowManager& m_window;

  double m_clickstart_x = 0.0;
  double m_clickstart_y = 0.0;
  int m_clickflags = 0;
  bool m_allowDrag = false;

};
