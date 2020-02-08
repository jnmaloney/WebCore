#pragma once


#include "SceneElement.h"
#include "RenderSystem.h" // For view


class OrbitCameraSceneElement : public SceneElement
{
public:
  OrbitCameraSceneElement()
  {
    VIEW_ELEMENT = true;
    INPUT_ELEMENT = true;
    UPDATE_ELEMENT = true;
    zoom(0);
  }


  ~OrbitCameraSceneElement() {}


  glm::vec3 getPos()
  {
    return pivot +
      radius *
      glm::vec3(
        sinf(heading) * cosf(pitch),
        cosf(heading) * cosf(pitch),
        sinf(pitch)
      );
  }


  void moveIt(double dx, double dy)
  {
    double worldx = -dx * cos(heading) + dy * sin(heading);
    double worldy = dx * sin(heading) + dy * cos(heading);
    pivot.x += -0.01 * worldx;
    pivot.y += -0.01 * worldy;
  }


  void zoom(int i)
  {
    zoomStep += i;
    if (zoomStep < 1) zoomStep = 1;
    if (zoomStep > 10) zoomStep = 10;
    targetRadius = 10.f + 0.5f * zoomStep * zoomStep;
  }


  void update(double dt)
  {
    float factor = 2.5f; // Zoom speed factor
    if (radius < targetRadius)
    {
      radius += factor * radius * dt;
      if (radius > targetRadius) radius = targetRadius;
    }
    else if (radius > targetRadius)
    {
      radius -= factor * radius * dt;
      if (radius < targetRadius) radius = targetRadius;
    }
  }


  int g_actionButton = GLFW_MOUSE_BUTTON_RIGHT;
  int g_cameraButton = GLFW_MOUSE_BUTTON_LEFT;
  int g_cancelButton = GLFW_MOUSE_BUTTON_RIGHT;


  void cursor_pos_callback(double xpos, double ypos)
  {
    g_xpos = xpos; g_ypos = ypos;

    if (move)
    {
      // // HACK THE CAMERA RAY
      // glm::vec3 pivot_reset = pivot;
      // pivot = worldMoveBeginPivot;
      //
      // glm::vec3 origin = getPos();
      // glm::vec3 ray1 = g_odin.rs.createRay(xpos, ypos);
      // float d = -origin.z / ray1.z;
      // glm::vec3 pos1 = origin + d * ray1;
      //
      // glm::vec3 moveVector = pos1 - worldMoveBeginClick;
      // pivot = worldMoveBeginPivot - moveVector;
    }

    if (orbit)
    {
      float dx = mouseBeginMoveX - g_xpos;
      float dy = mouseBeginMoveY - g_ypos;

      heading = beginHeading + dx * (-0.75f / 360.f);
      pitch = beginPitch + dy * (-0.75f / 360.f);
    }
  }


  void mouse_button_callback(int button, int action, int mods)
  {
    if (button == g_actionButton && action == GLFW_PRESS)
    {
      orbit = true;
      beginPitch = pitch;
      beginHeading = heading;
      mouseBeginMoveX = g_xpos;
      mouseBeginMoveY = g_ypos;
    }

    if (button == g_cameraButton && action == GLFW_PRESS)
    {
      // Trigger camera movement
      move = true;//(action == GLFW_PRESS);
      // mouseBeginMoveX = g_xpos;
      // mouseBeginMoveY = g_ypos;
      worldMoveBeginPivot = pivot;

      // Calculate world begin click ray (camera move)
      glm::vec3 origin = getPos();
      // glm::vec3 ray0 = g_odin.rs.createRay(g_xpos, g_ypos);
      // float d = -origin.z / ray0.z;
      worldMoveBeginClick = origin;// + d * ray0;
    }

    if (button == g_actionButton && action == GLFW_RELEASE)
    {
      orbit = false;
    }

    if (button == g_cameraButton && action == GLFW_RELEASE)
    {
      move = false;
    }

    if (button == g_cancelButton && action == GLFW_PRESS)
    {
    }
  }


  void scroll_callback(double xoffset, double yoffset)
  {
    if (yoffset > 0.0) zoom( 1);
    if (yoffset < 0.0) zoom(-1);
  }


  void view(RenderSystem* rs)
  {
    rs->setCameraPos(getPos(), pivot);
  }


protected:
  float radius = 20.f;
  float targetRadius = radius;
  int zoomStep = 8;


  bool move = false;
  bool orbit = false;

  //float heading = 0.7853982f;
  float heading = 0.0f;
  //float pitch = 1.047198f;
  float pitch = 1.18;

  glm::vec3 pivot;

  double mouseBeginMoveX = 0;
  double mouseBeginMoveY = 0;

  glm::vec3 worldMoveBeginClick;
  glm::vec3 worldMoveBeginPivot;

  float beginHeading = 0.0f;
  float beginPitch = 0.0f;


  bool m_mouseDrag = false;
  double g_xpos = 0;
  double g_ypos = 0;
};
