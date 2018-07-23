#include "InputSystem.h"



InputSystem::InputSystem(RenderSystem* rs) : m_rs(rs)
{
}


InputSystem::~InputSystem()
{


}


void InputSystem::cursor_pos_callback(double xpos, double ypos)
{
  m_cursor_x = xpos;
  m_cursor_y = ypos;


    if (m_clickflags & (1<<GLFW_MOUSE_BUTTON_RIGHT))
    {
      double dx = m_clickstart_x - m_cursor_x;
      double dy = m_clickstart_y - m_cursor_y;
      m_clickstart_x = m_cursor_x;
      m_clickstart_y = m_cursor_y;
      m_rs->move(dx, dy);
    }
}


void InputSystem::mouse_button_callback(int button, int action, int mods)
{
  //if (button == GLFW_MOUSE_BUTTON_RIGHT)
  {
    if (action == GLFW_PRESS && m_clickflags == 0)
    {
        m_clickflags |= (1<<button);
        m_clickstart_x = m_cursor_x;
        m_clickstart_y = m_cursor_y;
    }
    else
    {
        m_clickflags &= ~(1<<button);
    }
  }
  
  // ..

  // Button released
  if (action == GLFW_RELEASE) m_allowDrag = false;

  if (m_allowDrag) return;
}


void InputSystem::frame()
{
}
