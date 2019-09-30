#include "Square.h"
#include <iostream>
#include "RenderSystem.h"


Square::Square()
{

}


Square::~Square()
{

}


void Square::bind(RenderSystem* rs)
{
  glEnableVertexAttribArray(rs->attribute_v_coord);
  glBindBuffer(GL_ARRAY_BUFFER, m_vbo_vertices);
  glVertexAttribPointer(
    rs->attribute_v_coord, // attribute
    4,                  // number of elements per vertex, here (x,y,z)
    GL_FLOAT,           // the type of each element
    GL_FALSE,           // take our values as-is
    0,                  // no extra data between each position
    0                   // offset of first element
  );

  //if (rs->attribute_v_uv != -1)

  glEnableVertexAttribArray(rs->attribute_v_uv);
  glBindBuffer(GL_ARRAY_BUFFER, m_vbo_uvs);
  glVertexAttribPointer(
    rs->attribute_v_uv, // attribute
    2,                  // number of elements per vertex, here (x,y,z)
    GL_FLOAT,           // the type of each element
    GL_FALSE,           // take our values as-is
    0,                  // no extra data between each position
    0                   // offset of first element
  );

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo_elements);
}


void Square::draw()
{
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);
}


void Square::initVerts(int tile_x, int tile_y)
{
  GLfloat vertices_position[16] = {
 		0.0, 0.0, 0.0, 1.0,
 		1.0, 0.0, 0.0, 1.0,
 		1.0, 1.0, 0.0, 1.0,
 		0.0, 1.0, 0.0, 1.0,
 	};

  GLfloat vertices_uv[8] = {
    (GLfloat)tile_x / (float)x_res,           (GLfloat)tile_y/(float)y_res,
    ((GLfloat)tile_x + 1.0f)/(float)x_res,   (GLfloat)tile_y/(float)y_res,
    ((GLfloat)tile_x + 1.0f)/(float)x_res,   ((GLfloat)tile_y + 1.0f)/(float)y_res,
    (GLfloat)tile_x/(float)x_res,           ((GLfloat)tile_y + 1.0f)/(float)y_res,
  };

  GLushort index[6] = {
    0, 1, 2,
    2, 3, 0
  };

  // Create a Vector Buffer Object that will store the vertices on video memory
 	glGenBuffers(1, &m_vbo_vertices);

 	// Allocate space and upload the data from CPU to GPU
 	glBindBuffer(GL_ARRAY_BUFFER, m_vbo_vertices);
 	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_position), vertices_position, GL_STATIC_DRAW);

  glGenBuffers(1, &m_vbo_uvs);
  glBindBuffer(GL_ARRAY_BUFFER, m_vbo_uvs);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_uv), vertices_uv, GL_STATIC_DRAW);

  glGenBuffers(1, &m_ibo_elements);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo_elements);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index), index, GL_STATIC_DRAW); // elements (faces)
}
