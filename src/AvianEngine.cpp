#include "AvianEngine.h"
#include "graphics.h"
#include "RenderSystem.h"
#include "RenderQueue.h"
#include "WindowManager.h"
#include "MenuManager.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "ImGuizmo.h"
#include <algorithm>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>


WindowManager g_windowManager;
RenderSystem g_rs;
MenuManager g_menuManager;


AvianEngine::AvianEngine()
{

}


AvianEngine::~AvianEngine()
{

}


void AvianEngine::init()
{
  g_windowManager.width = settings.screen_size_x;
  g_windowManager.height = settings.screen_size_y;
  g_windowManager.init("Project");

  g_menuManager.init(g_windowManager);

  // depends on window..
  g_rs.init();

  // depends on window..
  glm::mat4 cameraProjection = glm::perspective(glm::radians(14.5f), (float)g_windowManager.width / (float)g_windowManager.height, 1.0f, 200.0f);
  g_rs.setViewProj(cameraProjection);
}


void AvianEngine::quit()
{
  glfwTerminate();
}


void AvianEngine::beginLoop()
{
  //g_rs.setViewProj(cameraProjection * cameraView);
  //m_renderWorld.draw(&g_rs);
  g_menuManager.predraw();

  g_rs.start();
}


void AvianEngine::endLoop()
{
  g_menuManager.postdraw();
}