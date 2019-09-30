#include "RenderQueue.h"
#include "Mesh.h"
#include <iostream>
#include "Texture.h"
#include "RenderSystem.h"
#include "MeshManager.h"


RenderQueue::RenderQueue()
{
}


RenderQueue::~RenderQueue()
{

}


void RenderQueue::clear()
{
  m_queue.clear();
}


void RenderQueue::setMVP(glm::mat4 mvp)
{
  m_currentTransform.x = mvp;
}


void RenderQueue::setTile(int t)
{
  m_queue[t];
  m_currentTransformLevel = &( m_queue[t] );
}


void RenderQueue::submit()
{
  m_currentTransformLevel->push_back(m_currentTransform);
}


void RenderQueue::draw(RenderSystem* rs)
{
  // For each tile...
  for (auto const tiles : m_queue)
  {
    // Set the tile to be drawn in this pass
    if (tiles.first == 0) continue;
    int t = tiles.first - 1;

    Square& square = m_tiles[t];
    if (square.m_vbo_vertices == -1) // Initialise
    {
      square.x_res = x_res;
      square.y_res = y_res;
      int x = t % mod_vert;
      int y = t / div_vert;
      square.initVerts(x, y);
    }

    // For each transform of the current tile...
    square.bind(rs);
    for (auto const transforms : tiles.second)
    {
      // Set the local transform matrix
      glUniformMatrix4fv(rs->uniformML, 1, GL_FALSE, &transforms.x[0][0]);

      //
      //              ----     DRAW     ----
      //
      square.draw();
    }
  }
}
