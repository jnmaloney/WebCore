#include "RenderQueueSceneElement.h"
#include "RenderQueue.h"
#include "RenderSystem.h"
#include "Texture.h"


RenderQueueSceneElement::RenderQueueSceneElement()
{

}


RenderQueueSceneElement::RenderQueueSceneElement(RenderQueue* rq, Texture* t)
{
  addRenderQueue(rq);
  m_texture = t;
}


RenderQueueSceneElement::~RenderQueueSceneElement()
{

}


void RenderQueueSceneElement::addRenderQueue(RenderQueue* rq)
{
  m_queues.push_back(rq);
}


void RenderQueueSceneElement::draw(RenderSystem* rs, MeshBank* mb)
{
  if (m_texture) m_texture->bind();
  for (auto& i: m_queues)
  {
    i->draw(rs);
  }
}
