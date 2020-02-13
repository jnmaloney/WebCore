#include "FollowCameraSceneElement.h"
#include "RenderSystem.h"


FollowCameraSceneElement::FollowCameraSceneElement(PhysicsLevel2D* level)
{
  m_level = level;
  UPDATE_ELEMENT = true;
  VIEW_ELEMENT = true;
}


FollowCameraSceneElement::~FollowCameraSceneElement()
{

}


void FollowCameraSceneElement::update(double dt)
{

}


void FollowCameraSceneElement::view(RenderSystem* rs)
{
  float x = 0.f;
  float y = 0.f;
  m_level->getDynamicPosition(&x, &y);

  y = 16 * 39.25; // Fixed-y

  rs->setCameraPos(
    glm::vec3(x, y, 200),
    glm::vec3(x, y, -10),
    glm::vec3(0, 1, 0));
}
