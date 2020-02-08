#include "SceneTileBatch.h"
#include "RenderSystem.h"
#include "MeshBank.h"
#include <stdio.h>
#include <iostream>
#include "Palette.h"


SceneTileBatch::SceneTileBatch()
{

}


SceneTileBatch::~SceneTileBatch()
{

}


void SceneTileBatch::init(int x, int y)
{
  m_x = x;
  m_y = y;
  m_squares.resize(x * y);
}


void SceneTileBatch::clear()
{
  // TODO
  m_tiles.clear();
}



void SceneTileBatch::addElement(int tileID, glm::mat4 xform)
{
  m_tiles[tileID].push_back(
    (TransformInfo)
    {
      xform
    }
  );
}


void SceneTileBatch::draw(RenderSystem* rs)
{
  // // glm::vec3 defaultColour = glm::vec3(1);
  // // rs->setProgramVec3(/*"diffuse", */defaultColour);
  //
  // for (auto tile : m_tiles)
  // {
  //   int id = tile.first;
  //
  //   for (auto xform : tile.second)
  //   {
  //     Square& square = m_squares[id];
  //     if (square.m_vbo_vertices == -1) // Initialise
  //     {
  //       square.x_res = m_x;
  //       square.y_res = m_y;
  //       int x = id % m_x;
  //       int y = id / m_x;
  //       square.initVerts(x, y);
  //     }
  //     //square.bind(rs);
  //     rs->bindSquare(&square);
  //     rs->drawMesh();
  //     //square.draw();
  //   }
  // }
}
