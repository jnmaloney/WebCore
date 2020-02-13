#pragma once


#include "SceneElement.h"
#include <map>
#include <string>
#include <vector>
#include <list>
#include <set>
#include <graphics.h>


class RenderQueue;
class Texture;


// Scene element "container" for RenderQueues
class RenderQueueSceneElement : public SceneElement
{
public:

  RenderQueueSceneElement();
  RenderQueueSceneElement(RenderQueue* rq, Texture* t);
  ~RenderQueueSceneElement();

  void addRenderQueue(RenderQueue* rq);

  void draw(RenderSystem* rs, MeshBank* mb);

protected:

  std::list<RenderQueue*> m_queues;
  Texture* m_texture = 0;
};
