#include "MenuManager.h"
#include <stdio.h>
#include <string.h>
#include <iostream>
#include "imgui.h"
#include "imgui_impl_glfw.h"
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
  //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls
  //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;   // Enable Gamepad Controls

  ImGui_ImplGlfw_InitForOpenGL(window.g_window, false);
  ImGui_ImplOpenGL3_Init();

  // Setup style
  //ImGui::StyleColorsDark();
  //ImGui::StyleColorsClassic();
  ImGui::StyleColorsLight();

  // Load Fonts
  io.Fonts->AddFontFromFileTTF("data/xkcd-script.ttf", 23.0f);
  // io.Fonts->AddFontFromFileTTF("data/xkcd-script.ttf", 18.0f);
  // io.Fonts->AddFontFromFileTTF("data/xkcd-script.ttf", 26.0f);
  m_headerFont =
  io.Fonts->AddFontFromFileTTF("data/xkcd-script.ttf", 48.0f);
  io.Fonts->AddFontDefault();

  imgui =  ImGui::GetCurrentContext();

  ImGuiStyle& style = ImGui::GetStyle();
  style.WindowBorderSize = 0;
  style.Colors[2/*"WindowBg"*/].w = 77.f / 255.f; // alpha
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

  //
  // Post Draw display?
  //
  // int display_w, display_h;
  // glfwMakeContextCurrent(window.g_window);
  // glfwGetFramebufferSize(window.g_window, &display_w, &display_h);
  // glViewport(0, 0, display_w, display_h);

  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
  //glfwMakeContextCurrent(window.g_window);
}


void MenuManager::window_display()
{
  /* - Rhythm display -
  ImVec2 pos(500.f, 0.f);
  ImVec2 pivot(0,0);
  ImGui::SetNextWindowPos(pos, 0, pivot);

  ImGui::Begin("Stats Window Long Title", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);

  ImGui::Text(m_display.c_str());
  ImGui::SameLine(0.0f, 120.f);

  ImGui::End();
  */
}
