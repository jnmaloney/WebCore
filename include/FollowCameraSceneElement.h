#pragma once


#include "SceneElement.h"
#include "PhysicsLevel2D.h"


class FollowCameraSceneElement : public SceneElement
{
public:

  FollowCameraSceneElement(PhysicsLevel2D* level);
  ~FollowCameraSceneElement();

  //
  // Update
  //
  void update(double dt);


  //
  // Viewing
  //
  void view(RenderSystem* rs);


protected:

  PhysicsLevel2D* m_level = 0;
};
