#pragma once


#include "SceneElement.h"
#include "PhysicsLevel2D.h"
#include "RenderQueue.h"
#include "Texture.h"
#include <vector>


class EnemySceneElement : public SceneElement
{
public:

  EnemySceneElement(PhysicsLevel2D* level);
  ~EnemySceneElement();

  void update(double dt);

  void draw(RenderSystem* rs, MeshBank* mb);

  void addEnemy(int type, float x, float y);

protected:

  PhysicsLevel2D* m_level = 0;

  RenderQueue m_queue;
  std::vector<Texture> m_textures;
  int m_currentFrame = 0;
  double m_timeCounter = 0.;

  class Enemy
  {
  public:
    Enemy() {}
    ~Enemy() {}
    int type = 0;
    btCollisionObject* collisionObject = 0;
  };
  std::vector<Enemy> m_enemies;

};
