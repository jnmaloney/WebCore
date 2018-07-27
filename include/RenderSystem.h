#pragma once
#include <string>
#include <vector>
#include "graphics.h"
#include "WindowManager.h"


// Controls the shaders and render loops
class RenderSystem
{

public:
  RenderSystem();
  ~RenderSystem();

  void init(WindowManager& window);

  void start();
  void end();

  bool enableVertexPos(GLint program);
  bool enableVertexUV(GLint program);

  // Move mouse cursor
  void setCursor(int x, int y);
  float m_cursorX = 0.f;
  float m_cursorY = 0.f;

  /*
    Non-UBO uniform updates
    Vertex buffer bindings (without changing formats)
    UBO binding
    Vertex format changes
    Texture bindings
    Fragment post-processing state changes
    Shader program changes
    Render target switches
  */
    // shader program
    // : vertex id
    // : normals id
    // : uv
    // : texture
    // MVP value (uniform)
    // Colour value (uniform)
    // Elements

  void move(double, double);

  // Camera move callback
  void zoom(int);
  GLint uniformML;
  GLint uniformVP;
  GLint uniformDiffuse;
  GLint uniformML2;
  GLint uniformVP2;
  GLint uniformDiffuse2;
  GLint uniformAlpha;

  // Vars
  long m_shader;
  GLuint programObject; // 1 Texture
  GLuint programObject2; // No textures

  // View settings
  double m_cameraX = 0.0;
  double m_cameraY = 0.0;
  int m_zoomFactor = 3;
  float m_zoom = 0.5 + 0.5 * (1<<3);

  // The window that we render to
  WindowManager& m_window = *WindowManager::getInstance();

  GLint att = 0;

protected:

  unsigned int m_default_framebuffer = 0;

  // Non - core



  // Uniforms OLD
  GLint uniform_s_GBuffer;
  GLint lightPos, lightCol;

  // Uniforms NEW
  GLint attribute_v_coord;
  GLint attribute_v_coord2;
  GLint attribute_v_uv;

};
