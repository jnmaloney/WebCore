#include "MenuManager.h"
#include <stdio.h>
#include <string>
#include <string.h>
#include <iostream>
#include "imgui.h"
#include "imgui_impl_glfw.h"
//#include "imgui_impl_opengl2.h"
#include "imgui_impl_opengl3.h"
#include <iostream>
#include <fstream>


int getFileImDir(std::ifstream& f)
{
  int i;
  f >> i;
  return i;
}


ImVec2 getFileImVec2(std::ifstream& f)
{
  int x, y;
  f >> x;
  f >> y;
  return ImVec2(x, y);
}


float getFileFloat(std::ifstream& f)
{
  float x;
  f >> x;
  return x;
}


ImVec4 getFileColour(std::ifstream& f)
{
  int r, g, b;
  float a;
  f >> r;
  f >> g;
  f >> b;
  f >> a;
  return ImVec4(r/255.0, g/255.0, b/255.0, a);
}


float getFileBool(std::ifstream& f)
{
  bool x;
  f >> x;
  return x;
}


MenuManager::MenuManager()
{

}


MenuManager::~MenuManager()
{

}


void MenuManager::init(WindowManager& window)
{
  // Create game objects
  // Setup Dear ImGui binding
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();

  ImGui_ImplGlfw_InitForOpenGL(window.g_window, true);
  //ImGui_ImplGlfw_InitForOpenGL(window.g_window, true);
  ImGui_ImplOpenGL3_Init();

  //setDefaultStyle();
  ImGui::StyleColorsLight();
}


void MenuManager::setDefaultStyle()
{
  ImGuiIO& io = ImGui::GetIO();
  //io.ConfigFlags |= ImGuiConfigFlags_NoMouse;
  //io.ConfigFlags |= ImGuiConfigFlags_IsTouchScreen;  // Touch
  //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls
  //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;   // Enable Gamepad Controls

  // Setup style
  //ImGui::StyleColorsDark();
  //ImGui::StyleColorsClassic();
  ImGui::StyleColorsLight();

  // Load Fonts
  io.Fonts->AddFontFromFileTTF(fontNameTTF.c_str(), 24.0f);
  //io.Fonts->AddFontFromFileTTF(fontNameTTF.c_str(), 42.0f);
  //io.Fonts->AddFontFromFileTTF("data/font/CabinSketch-Bold.ttf", 32.0f);
  //io.Fonts->AddFontFromFileTTF("data/font/Voltaire-Regular.ttf", 23.0f);
//  io.Fonts->AddFontFromFileTTF("data/xkcd-script.ttf", 18.0f);
//  io.Fonts->AddFontFromFileTTF("data/xkcd-script.ttf", 26.0f);
  m_headerFont =
  io.Fonts->AddFontFromFileTTF(fontNameTTF.c_str(), 48.0f);
  //io.Fonts->AddFontFromFileTTF("data/font/CabinSketch-Bold.ttf", 48.0f);
//  io.Fonts->AddFontFromFileTTF("data/xkcd-script.ttf", 48.0f);
  io.Fonts->AddFontDefault();

  imgui =  ImGui::GetCurrentContext();

  ImGuiStyle& style = ImGui::GetStyle();
  style.FrameBorderSize = 0;
  style.WindowBorderSize = 0;
  style.GrabRounding = 0;
  style.WindowRounding = 0;
  style.FrameRounding = 0;
  style.WindowPadding = ImVec2(0.f, 0.f);
  style.FramePadding = ImVec2(0.f, 0.f);

  //style.Colors[2/*"WindowBg"*/].w = 77.f / 255.f; // alpha
  //style.Colors[13/*"MenuBg"*/].w = 77.f / 255.f; // alpha

  // style.Colors[0/*"text"*/].x = 1.f;
  // style.Colors[0/*"text"*/].y = 1.f;
  // style.Colors[0/*"text"*/].z = 1.f;
  style.Colors[2/*"WindowBg"*/].w = 0.f / 255.f; // alpha

  // Adventure Town
  // style.Colors[ImGuiCol_ButtonActive] = ImVec4(255.0/255.0, 246.0/255.0, 211.0/255.0, 1.0);
  // style.Colors[ImGuiCol_ButtonHovered] = ImVec4(218.0/255.0, 122.0/255.0, 52.0/255.0, 1.0);
  // style.Colors[ImGuiCol_Button] = ImVec4(142.0/255.0, 47.0/255.0, 21.0/255.0, 1.0);

  // Space
  style.Colors[0/*"text"*/] = ImVec4(255.0/255.0, 255.0/255.0, 255.0/255.0, 1.0);
  style.Colors[ImGuiCol_ButtonActive] = ImVec4(255.0/255.0, 246.0/255.0, 211.0/255.0, 1.0);
  style.Colors[ImGuiCol_ButtonHovered] = ImVec4(96.0/255.0, 33.0/255.0, 91.0/255.0, 1.0);
  style.Colors[ImGuiCol_Button] = ImVec4(53.0/255.0, 29.0/255.0, 73.0/255.0, 1.0);
  style.Colors[ImGuiCol_FrameBg] = ImVec4(96.0/255.0, 33.0/255.0, 91.0/255.0, 1.0);

}


void MenuManager::setStyleSheet(const char* filename)
{
  std::ifstream f;
  f.open(filename);

  ImGuiStyle& style = ImGui::GetStyle();

  std::string token;
  while (!f.eof())
  {
    f >> token;
    if (token.compare("style") == 0)
    {
      f >> token;
      if (token.compare("light") == 0)
        ImGui::StyleColorsLight();
      if (token.compare("dark") == 0)
        ImGui::StyleColorsDark();
      if (token.compare("classic") == 0)
        ImGui::StyleColorsClassic();
    }
    if (token.compare("fontname") == 0)
      f >> fontNameTTF;
      
    if (token.compare("Alpha") == 0)
      style.Alpha = getFileFloat(f);
    if (token.compare("WindowPadding") == 0)
      style.WindowPadding = getFileImVec2(f);
    if (token.compare("WindowRounding") == 0)
      style.WindowRounding = getFileFloat(f);
    if (token.compare("WindowBorderSize") == 0)
      style.WindowBorderSize = getFileFloat(f);
    if (token.compare("WindowMinSize") == 0)
      style.WindowMinSize = getFileImVec2(f);
    if (token.compare("WindowTitleAlign") == 0)
      style.WindowTitleAlign = getFileImVec2(f);
    if (token.compare("WindowMenuButtonPosition") == 0)
      style.WindowMenuButtonPosition = getFileImDir(f);
    if (token.compare("ChildRounding") == 0)
      style.ChildRounding = getFileFloat(f);
    if (token.compare("ChildBorderSize") == 0)
      style.ChildBorderSize = getFileFloat(f);
    if (token.compare("PopupRounding") == 0)
      style.PopupRounding = getFileFloat(f);
    if (token.compare("PopupBorderSize") == 0)
      style.PopupBorderSize = getFileFloat(f);
    if (token.compare("FramePadding") == 0)
      style.FramePadding = getFileImVec2(f);
    if (token.compare("FrameRounding") == 0)
      style.FrameRounding = getFileFloat(f);
    if (token.compare("FrameBorderSize") == 0)
      style.FrameBorderSize = getFileFloat(f);
    if (token.compare("ItemSpacing") == 0)
      style.ItemSpacing = getFileImVec2(f);
    if (token.compare("ItemInnerSpacing") == 0)
      style.ItemInnerSpacing = getFileImVec2(f);
    if (token.compare("TouchExtraPadding") == 0)
      style.TouchExtraPadding = getFileImVec2(f);
    if (token.compare("IndentSpacing") == 0)
      style.IndentSpacing = getFileFloat(f);
    if (token.compare("ColumnsMinSpacing") == 0)
      style.ColumnsMinSpacing = getFileFloat(f);
    if (token.compare("ScrollbarSize") == 0)
      style.ScrollbarSize = getFileFloat(f);
    if (token.compare("ScrollbarRounding") == 0)
      style.ScrollbarRounding = getFileFloat(f);
    if (token.compare("GrabMinSize") == 0)
      style.GrabMinSize = getFileFloat(f);
    if (token.compare("GrabRounding") == 0)
      style.GrabRounding = getFileFloat(f);
    if (token.compare("TabRounding") == 0)
      style.TabRounding = getFileFloat(f);
    if (token.compare("TabBorderSize") == 0)
      style.TabBorderSize = getFileFloat(f);
    if (token.compare("ColorButtonPosition") == 0)
      style.ColorButtonPosition = getFileImDir(f);
    if (token.compare("ButtonTextAlign") == 0)
      style.ButtonTextAlign = getFileImVec2(f);
    if (token.compare("SelectableTextAlign") == 0)
      style.SelectableTextAlign = getFileImVec2(f);
    if (token.compare("DisplayWindowPadding") == 0)
      style.DisplayWindowPadding = getFileImVec2(f);
    if (token.compare("DisplaySafeAreaPadding") == 0)
      style.DisplaySafeAreaPadding = getFileImVec2(f);
    if (token.compare("MouseCursorScale") == 0)
      style.MouseCursorScale = getFileFloat(f);
    if (token.compare("AntiAliasedLines") == 0)
      style.AntiAliasedLines = getFileBool(f);
    if (token.compare("AntiAliasedFill") == 0)
      style.AntiAliasedFill = getFileBool(f);
    if (token.compare("CurveTessellationTol") == 0)
      style.CurveTessellationTol = getFileFloat(f);
    if (token.compare("CircleSegmentMaxError") == 0)
      style.CircleSegmentMaxError = getFileFloat(f);

    // Colours
    if (token.compare("C") == 0)
    {
        f >> token;
        if (token.compare("ImGuiCol_Text") == 0)
          style.Colors[ImGuiCol_Text] = getFileColour(f);
        if (token.compare("ImGuiCol_TextDisabled") == 0)
          style.Colors[ImGuiCol_TextDisabled] = getFileColour(f);
        if (token.compare("ImGuiCol_WindowBg") == 0)
          style.Colors[ImGuiCol_WindowBg] = getFileColour(f);
        if (token.compare("ImGuiCol_ChildBg") == 0)
          style.Colors[ImGuiCol_ChildBg] = getFileColour(f);
        if (token.compare("ImGuiCol_PopupBg") == 0)
          style.Colors[ImGuiCol_PopupBg] = getFileColour(f);
        if (token.compare("ImGuiCol_Border") == 0)
          style.Colors[ImGuiCol_Border] = getFileColour(f);
        if (token.compare("ImGuiCol_BorderShadow") == 0)
          style.Colors[ImGuiCol_BorderShadow] = getFileColour(f);
        if (token.compare("ImGuiCol_FrameBg") == 0)
          style.Colors[ImGuiCol_FrameBg] = getFileColour(f);
        if (token.compare("ImGuiCol_FrameBgHovered") == 0)
          style.Colors[ImGuiCol_FrameBgHovered] = getFileColour(f);
        if (token.compare("ImGuiCol_FrameBgActive") == 0)
          style.Colors[ImGuiCol_FrameBgActive] = getFileColour(f);
        if (token.compare("ImGuiCol_TitleBg") == 0)
          style.Colors[ImGuiCol_TitleBg] = getFileColour(f);
        if (token.compare("ImGuiCol_TitleBgActive") == 0)
          style.Colors[ImGuiCol_TitleBgActive] = getFileColour(f);
        if (token.compare("ImGuiCol_TitleBgCollapsed") == 0)
          style.Colors[ImGuiCol_TitleBgCollapsed] = getFileColour(f);
        if (token.compare("ImGuiCol_MenuBarBg") == 0)
          style.Colors[ImGuiCol_MenuBarBg] = getFileColour(f);
        if (token.compare("ImGuiCol_ScrollbarBg") == 0)
          style.Colors[ImGuiCol_ScrollbarBg] = getFileColour(f);
        if (token.compare("ImGuiCol_ScrollbarGrab") == 0)
          style.Colors[ImGuiCol_ScrollbarGrab] = getFileColour(f);
        if (token.compare("ImGuiCol_ScrollbarGrabHovered") == 0)
          style.Colors[ImGuiCol_ScrollbarGrabHovered] = getFileColour(f);
        if (token.compare("ImGuiCol_ScrollbarGrabActive") == 0)
          style.Colors[ImGuiCol_ScrollbarGrabActive] = getFileColour(f);
        if (token.compare("ImGuiCol_CheckMark") == 0)
          style.Colors[ImGuiCol_CheckMark] = getFileColour(f);
        if (token.compare("ImGuiCol_SliderGrab") == 0)
          style.Colors[ImGuiCol_SliderGrab] = getFileColour(f);
        if (token.compare("ImGuiCol_SliderGrabActive") == 0)
          style.Colors[ImGuiCol_SliderGrabActive] = getFileColour(f);
        if (token.compare("ImGuiCol_Button") == 0)
          style.Colors[ImGuiCol_Button] = getFileColour(f);
        if (token.compare("ImGuiCol_ButtonHovered") == 0)
          style.Colors[ImGuiCol_ButtonHovered] = getFileColour(f);
        if (token.compare("ImGuiCol_ButtonActive") == 0)
          style.Colors[ImGuiCol_ButtonActive] = getFileColour(f);
        if (token.compare("ImGuiCol_HeaderHovered") == 0)
          style.Colors[ImGuiCol_HeaderHovered] = getFileColour(f);
        if (token.compare("ImGuiCol_HeaderActive") == 0)
          style.Colors[ImGuiCol_HeaderActive] = getFileColour(f);
        if (token.compare("ImGuiCol_Separator") == 0)
          style.Colors[ImGuiCol_Separator] = getFileColour(f);
        if (token.compare("ImGuiCol_SeparatorHovered") == 0)
          style.Colors[ImGuiCol_SeparatorHovered] = getFileColour(f);
        if (token.compare("ImGuiCol_SeparatorActive") == 0)
          style.Colors[ImGuiCol_SeparatorActive] = getFileColour(f);
        if (token.compare("ImGuiCol_ResizeGrip") == 0)
          style.Colors[ImGuiCol_ResizeGrip] = getFileColour(f);
        if (token.compare("ImGuiCol_ResizeGripHovered") == 0)
          style.Colors[ImGuiCol_ResizeGripHovered] = getFileColour(f);
        if (token.compare("ImGuiCol_ResizeGripActive") == 0)
          style.Colors[ImGuiCol_ResizeGripActive] = getFileColour(f);
        if (token.compare("ImGuiCol_Tab") == 0)
          style.Colors[ImGuiCol_Tab] = getFileColour(f);
        if (token.compare("ImGuiCol_TabHovered") == 0)
          style.Colors[ImGuiCol_TabHovered] = getFileColour(f);
        if (token.compare("ImGuiCol_TabActive") == 0)
          style.Colors[ImGuiCol_TabActive] = getFileColour(f);
        if (token.compare("ImGuiCol_TabUnfocused") == 0)
          style.Colors[ImGuiCol_TabUnfocused] = getFileColour(f);
        if (token.compare("ImGuiCol_TabUnfocusedActive") == 0)
          style.Colors[ImGuiCol_TabUnfocusedActive] = getFileColour(f);
        if (token.compare("ImGuiCol_PlotLines") == 0)
          style.Colors[ImGuiCol_PlotLines] = getFileColour(f);
        if (token.compare("ImGuiCol_PlotLinesHovered") == 0)
          style.Colors[ImGuiCol_PlotLinesHovered] = getFileColour(f);
        if (token.compare("ImGuiCol_PlotHistogram") == 0)
          style.Colors[ImGuiCol_PlotHistogram] = getFileColour(f);
        if (token.compare("ImGuiCol_PlotHistogramHovered") == 0)
          style.Colors[ImGuiCol_PlotHistogramHovered] = getFileColour(f);
        if (token.compare("ImGuiCol_TextSelectedBg") == 0)
          style.Colors[ImGuiCol_TextSelectedBg] = getFileColour(f);
        if (token.compare("ImGuiCol_DragDropTarget") == 0)
          style.Colors[ImGuiCol_DragDropTarget] = getFileColour(f);
        if (token.compare("ImGuiCol_NavHighlight") == 0)
          style.Colors[ImGuiCol_NavHighlight] = getFileColour(f);
        if (token.compare("ImGuiCol_NavWindowingHighlight") == 0)
          style.Colors[ImGuiCol_NavWindowingHighlight] = getFileColour(f);
        if (token.compare("ImGuiCol_NavWindowingDimBg") == 0)
          style.Colors[ImGuiCol_NavWindowingDimBg] = getFileColour(f);
        if (token.compare("ImGuiCol_ModalWindowDimBg") == 0)
          style.Colors[ImGuiCol_ModalWindowDimBg] = getFileColour(f);
    }
  }
}


void MenuManager::predraw()
{
  //
  // Pre Draw
  //
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();
}


void MenuManager::postdraw()
{
  //
  // Do stuff
  //
  //window_display();
  ImGui::Render();
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}


void MenuManager::window_display()
{
}
