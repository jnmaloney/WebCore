#include "MenuManager.h"
#include <stdio.h>
#include <string.h>
#include <iostream>
#include "imgui.h"
#include "imgui_impl_glfw.h"
//#include "imgui_impl_opengl2.h"
#include "imgui_impl_opengl3.h"


static ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
static bool show_demo_window = true;
static bool show_another_window = false;


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
  ImGuiIO& io = ImGui::GetIO();
  //io.ConfigFlags |= ImGuiConfigFlags_NoMouse;
  //io.ConfigFlags |= ImGuiConfigFlags_IsTouchScreen;  // Touch
  //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls
  //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;   // Enable Gamepad Controls

  ImGui_ImplGlfw_InitForOpenGL(window.g_window, true);
  //ImGui_ImplGlfw_InitForOpenGL(window.g_window, true);
  ImGui_ImplOpenGL3_Init();

  // Setup style
  //ImGui::StyleColorsDark();
  //ImGui::StyleColorsClassic();
  ImGui::StyleColorsLight();

  // Load Fonts
  //io.Fonts->AddFontFromFileTTF(fontNameTTF.c_str(), 24.0f);
  io.Fonts->AddFontFromFileTTF(fontNameTTF.c_str(), 42.0f);
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


void MenuManager::predraw()
{
  //
  // Pre Draw
  //
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();
}


void MenuManager::postdraw(WindowManager& window)
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
