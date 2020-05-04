#ifdef 0
#include "CharacterControllerSceneElement.h"
#include "RenderSystem.h"


CharacterControllerSceneElement::CharacterControllerSceneElement(PhysicsLevel2D* level)
{
  m_level = level;
  INPUT_ELEMENT = true;
  UPDATE_ELEMENT = true;
}


CharacterControllerSceneElement::~CharacterControllerSceneElement()
{

}


void CharacterControllerSceneElement::update(double dt)
{
  if (m_state.mJump)
  {
    // Wall jump left
    if (PhysicsLevel2D::contactLeft[1] - PhysicsLevel2D::contactLeft[0] > 0)
    {
      m_level->jumpDynamicWall(1);
      m_state.mJump = false;
    }
    // Wall jump right
    else if (PhysicsLevel2D::contactRight[1] - PhysicsLevel2D::contactRight[0] > 0)
    {
      m_level->jumpDynamicWall(-1);
      m_state.mJump = false;
    }
    // Ground jump
    else if (PhysicsLevel2D::contactTop[1] - PhysicsLevel2D::contactTop[0] > -140)
    {
      m_level->jumpDynamic();
      m_state.mJump = false;
    }
  }

  if (m_state.mRight)
  {
    m_level->addDynamicImpulse(1);
    m_state.mFacingRight = true;
  }
  else
  if (m_state.mLeft)
  {
    m_level->addDynamicImpulse(-1);
    m_state.mFacingRight = false;
  }
  else
  {
    m_level->addDynamicImpulse(0);
  }
}


void CharacterControllerSceneElement::key_callback(int key, int scancode, int action, int mods)
{
  if (action == GLFW_PRESS)
  {
    if (key == GLFW_KEY_RIGHT)
    {
      m_state.mRight = true;
    }

    if (key == GLFW_KEY_LEFT)
    {
      m_state.mLeft = true;
    }

    if (key == GLFW_KEY_Z)
    {
      m_state.mJump = true;
    }
  }

  if (action == GLFW_RELEASE)
  {
    if (key == GLFW_KEY_RIGHT)
    {
      m_state.mRight = false;
    }

    if (key == GLFW_KEY_LEFT)
    {
      m_state.mLeft = false;
    }

    if (key == GLFW_KEY_Z)
    {
      m_state.mJump = false;
    }
  }
}

#endif
