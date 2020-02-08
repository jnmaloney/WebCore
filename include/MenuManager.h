#pragma once


#include <string>
#include "WindowManager.h"


class ImGuiContext;
class ImFont;


class MenuManager
{
public:

  MenuManager();
  ~MenuManager();

  void init(WindowManager& window);

  //void draw(WindowManager& window);
  void predraw();
  void postdraw();

  ImGuiContext* imgui = 0;

  std::string m_display = "\t\t\tWaiting...";

  ImFont* m_headerFont = 0;

  std::string fontNameTTF = "data/font/your-quota.ttf";

  void setDefaultStyle();
  void setStyleSheet(const char* sheet);

protected:
  void window_display();
};
