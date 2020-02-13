#pragma once


#include "SceneElement.h"
#include "PhysicsLevel2D.h"
#include "RenderQueue.h"
#include "Texture.h"
#include <vector>
#include "CharacterControllerSceneElement.h"


class CharacterRenderSceneElement : public SceneElement
{
public:

  CharacterRenderSceneElement(
    PhysicsLevel2D* level,
    CharacterControllerSceneElement::CharacterState* state);
  ~CharacterRenderSceneElement();

  void update(double dt);

  void draw(RenderSystem* rs, MeshBank* mb);

protected:

  PhysicsLevel2D* m_level = 0;
  CharacterControllerSceneElement::CharacterState* m_state = 0;

  RenderQueue m_queue;
  std::vector<Texture> m_textures;
  int m_currentFrame = 0;


  class FrameSequence
  {
  public:
    FrameSequence() {}

    FrameSequence(std::vector<int> a_frames)
    {
      frames = a_frames;
    }


    ~FrameSequence()
    {

    }


    void advance(double dt)
    {
      double framerate = 0.2;
      t += dt;
      if (t > framerate)
      {
        t -= framerate;
        i = (i + 1) % frames.size();
        frame = frames[i];
      }
    }


    int frame = 0;

  private:
    double t = 0.;
    int i = 0;
    std::vector<int> frames;
  };

  FrameSequence m_idleSequence;
  FrameSequence m_runSequence;
};
