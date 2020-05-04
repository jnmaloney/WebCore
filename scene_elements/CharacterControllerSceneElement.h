#pragma once
#ifdef 0

#include "SceneElement.h"
#include "PhysicsLevel2D.h"


class CharacterControllerSceneElement : public SceneElement
{
public:

  CharacterControllerSceneElement(PhysicsLevel2D* level);
  ~CharacterControllerSceneElement();

  void update(double dt);

  void key_callback(int key, int scancode, int action, int mods);

  class CharacterState
  {
  public:
    CharacterState() {}
    bool mJumping = false;
    bool mFalling = false;
    bool mWallRight = false;
    bool mWallLeft = false;
    bool mWallGrip = false;
    bool mClearWallLeft = true;
    bool mClearWallRight = true;

    // Which way are you trying to move
    bool mRight = false;
    bool mLeft = false;
    int mJump = 0;

    bool mFacingRight = true;
    bool mGrounded = true;
  };

  CharacterState m_state;

protected:

  PhysicsLevel2D* m_level = 0;
};

#endif
