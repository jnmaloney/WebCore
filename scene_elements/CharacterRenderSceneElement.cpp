#include "CharacterRenderSceneElement.h"
#include "RenderSystem.h"


CharacterRenderSceneElement::CharacterRenderSceneElement(PhysicsLevel2D* level, CharacterControllerSceneElement::CharacterState* state)
{
  m_level = level;
  m_state = state;
  DRAW_ELEMENT = true;
  UPDATE_ELEMENT = true;

  m_textures.resize(8);
  m_textures[0].loadPng("data/img/ninja/run1.png");
  m_textures[1].loadPng("data/img/ninja/run2.png");
  m_textures[2].loadPng("data/img/ninja/run3.png");
  m_textures[3].loadPng("data/img/ninja/run4.png");
  m_textures[4].loadPng("data/img/ninja/run5.png");
  m_textures[5].loadPng("data/img/ninja/jump.png");
  m_textures[6].loadPng("data/img/ninja/ledgegrab.png");
  m_textures[7].loadPng("data/img/ninja/wallslide.png");
  // Idle seq: 1, 2
  // Run seq: 3, 4, 5, 4
  m_idleSequence = FrameSequence(std::vector<int>({0, 1}));
  m_runSequence = FrameSequence(std::vector<int>({3, 4}));


  m_queue.setSheet(1, 1);
}


CharacterRenderSceneElement::~CharacterRenderSceneElement()
{

}


void CharacterRenderSceneElement::update(double dt)
{
  m_queue.clear();

  float x, y;
  m_level->getDynamicPosition(&x, &y);
  float z = -10.f;

  glm::mat4 mvp(1.0);

  // mvp = glm::translate(mvp,
  //   glm::vec3(
  //     x - 8.f,
  //     y - 8.f,
  //     z));
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

  if (m_state->mFacingRight == false)
  {
    mvp = glm::translate(mvp,
      glm::vec3(
        1.f,
        0,
        0));
    mvp = glm::scale(mvp,
      glm::vec3(
        -1,
        1,
        1));
  }

  // stamp
  m_queue.setTile(1);
  m_queue.setMVP(mvp);
  m_queue.submit();

  // Anim.
  if (m_state->mLeft || m_state->mRight)
  {
    m_runSequence.advance(dt);
    m_currentFrame = m_runSequence.frame;
  }
  else
  {
    m_idleSequence.advance(dt);
    m_currentFrame = m_idleSequence.frame;
  }

  // hmmm manifolds
  if (PhysicsLevel2D::contactLeft[0] - y <= 56 && PhysicsLevel2D::contactLeft[1] - y >= -58)
  {
    m_currentFrame = 7;
  }
  if (PhysicsLevel2D::contactRight[0] - y <= 56 && PhysicsLevel2D::contactRight[1] - y >= -58)
  {
    m_currentFrame = 7;
  }
}


void CharacterRenderSceneElement::draw(RenderSystem* rs, MeshBank* mb)
{
  m_textures[m_currentFrame].bind();
  m_queue.draw(rs);
}
