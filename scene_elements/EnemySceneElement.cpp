#include "EnemySceneElement.h"


EnemySceneElement::EnemySceneElement(PhysicsLevel2D* level)
{
  m_level = level;
  DRAW_ELEMENT = true;
  UPDATE_ELEMENT = true;
}


EnemySceneElement::~EnemySceneElement()
{

}


void EnemySceneElement::update(double dt)
{
  // Create render queue for all enemies
  m_queue.clear();

  for (auto& i: m_enemies)
  {
    glm::mat4 mvp(1.0);

    btTransform t = i.collisionObject->getWorldTransform();
    btVector3 v = t.getOrigin();

    float x = v.x();
    float y = v.y();
    float z = -5;

    mvp = glm::translate(mvp, // Pixel offset
      glm::vec3(
        x - 7.f,
        y - 10.f,
        z));

    mvp = glm::scale(mvp,
      glm::vec3(
        16,
        16,
        1));

    // stamp
    m_queue.setTile(1);
    m_queue.setMVP(mvp);
    m_queue.submit();
  }
}


void EnemySceneElement::draw(RenderSystem* rs, MeshBank* mb)
{
  m_queue.draw(rs);
}


void EnemySceneElement::addEnemy(int type, float x, float y)
{
  Enemy enemy;
  enemy.type = type;
  enemy.collisionObject = m_level->addEnemy(x, x+10, y, y+10, this);
  m_enemies.push_back(enemy);
}
