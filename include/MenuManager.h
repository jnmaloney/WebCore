#pragma once


#include <string>
#include "WindowManager.h"


class ImGuiContext;


class MenuManager
{
public:

  MenuManager();
  ~MenuManager();

  void init(WindowManager& window);

  //void draw(WindowManager& window);
  void predraw();
  void postdraw(WindowManager& window);

  ImGuiContext* imgui = 0;

  std::string m_display = "\t\t\tWaiting...";

protected:
  void window_display();
};
