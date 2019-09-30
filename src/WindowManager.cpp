#include "WindowManager.h"
#include <stdio.h>
#include <string.h>
#include <iostream>


WindowManager* WindowManager::s_currentInstance = 0;


void window_size_callback(GLFWwindow* window, int width, int height)
{
  WindowManager::getInstance()->width = width;
  WindowManager::getInstance()->height = height;
}


WindowManager::WindowManager()
{
  s_currentInstance = this;
}


WindowManager::~WindowManager()
{
  glfwTerminate();
}


int WindowManager::init(const char* title)
{
  if( !glfwInit() )
  {
      //fprintf( stderr, "Failed to initialize GLFW\n" );
      fprintf( stdout, "Failed to initialize GLFW\n" );
      return 1;
  }

  //glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // We don't want the old OpenGL

  // Open a window and create its OpenGL context
  g_window = glfwCreateWindow( width, height, title, NULL, NULL);
  if( g_window == NULL )
  {
      //fprintf( stderr, "Failed to open GLFW window.\n" );
      fprintf( stdout, "Failed to open GLFW window.\n" );
      glfwTerminate();
      return -1;
  }
  glfwMakeContextCurrent(g_window); // Initialize GLEW

  // Window size callback
  glfwSetWindowSizeCallback(g_window, window_size_callback);
  glfwSetFramebufferSizeCallback(g_window, window_size_callback);

  return 0;
}


glm::vec4 WindowManager::getViewport()
{
  return glm::vec4(0.f, 0.f, (float)width, (float)height);
}
