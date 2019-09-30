#include "InputSystem.h"
// Callbacks
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"


InputSystem::InputSystem(WindowManager& rs) : m_window(rs)
{
}


InputSystem::~InputSystem()
{


}


void InputSystem::cursor_pos_callback(double xpos, double ypos)
{
  m_cursor_x = xpos;
  m_cursor_y = ypos;

  // Touch?
  //ImGui::GetIO().MousePos = ImVec2((float)xpos, (float)ypos);
}


void InputSystem::mouse_button_callback(int button, int action, int mods)
{
  // Touch?
  // ImGuiIO& io = ImGui::GetIO();
  // io.MousePos = ImVec2((float)m_cursor_x, (float)m_cursor_y);
  // io.MouseDown[0] = (button == GLFW_MOUSE_BUTTON_LEFT) && (action == GLFW_PRESS);
  // ImGui_ImplGlfw_MouseButtonCallback(m_window.g_window, button, action, mods);

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


void InputSystem::key_callback(int key, int scancode, int action, int mods)
{
  ImGui_ImplGlfw_KeyCallback(m_window.g_window, key, scancode, action, mods);
}


void InputSystem::char_callback(unsigned int button)
{
  ImGui_ImplGlfw_CharCallback(m_window.g_window, button);
}


bool InputSystem::captureMouse()
{
  return ImGui::GetIO().WantCaptureMouse;
}


void InputSystem::frame()
{
}
