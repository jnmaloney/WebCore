#include "RenderQueue.h"
#include "Mesh.h"
#include <iostream>
#include "Texture.h"


RenderQueue::RenderQueue()
{

}


RenderQueue::~RenderQueue()
{

}


void RenderQueue::clear()
{
  m_programs.clear();
}


void RenderQueue::setProgram(GLint program)
{
  //std::cout << "Set Prog " << m_programs.size() << std::endl;
  m_programs[program];
  m_currentMeshLevel = &( m_programs[program] );
  //std::cout << "Set Prog " << m_programs.size() << std::endl;
}


void RenderQueue::setMesh(Mesh* mesh)
{
  //std::cout << "Set Mesh " << (m_currentMeshLevel ? m_currentMeshLevel->size() : 0) << std::endl;

  (*m_currentMeshLevel)[mesh];
  m_currentTransformLevel = &( (*m_currentMeshLevel)[mesh] );

  //std::cout << "Set Mesh " << m_currentMeshLevel->size() << std::endl;


  //for (auto const programs : m_programs )
  // for (auto programs = m_programs.begin(); programs != m_programs.end(); ++programs )
  // {
  //   std::cout << "Programs " << programs->first << "\t" << programs->second.size() << std::endl;
  //   //for (auto meshes : programs->second )
  //   for (auto meshes = programs->second.begin(); meshes != programs->second.end(); ++meshes )
  //   {
  //     std::cout << "Meshes " << std::endl;
  //   }
  // }
}


void RenderQueue::setMVP(glm::mat4 mvp)
{
  //std::cout << "Set MVP " << m_currentTransformLevel->size() << std::endl;
  m_currentTransformLevel->push_back(mvp);
  //std::cout << "Set MVP " << m_currentTransformLevel->size() << std::endl;
}


void RenderQueue::submit()
{
  // Add elements to ElementLevel
}


void RenderQueue::draw(GLint uniformMVP, GLint uniformDiffuse)
{
  //std::cout << "draw() " << m_programs.size() << std::endl;

  for (auto const programs : m_programs )
  {
    //std::cout << "Programs " << programs.first << "\t" << programs.second.size() << std::endl;
    // setProgram(programs.first)
    for (auto const meshes : programs.second )
    {
      //std::cout << "Meshes " << std::endl;
      // Bind the mesh verts

      Mesh* mesh = meshes.first;

      glEnableVertexAttribArray(mesh->attribute_v_coord);

      // Describe our vertices array to OpenGL (it can't guess its format automatically)
      glBindBuffer(GL_ARRAY_BUFFER, mesh->m_vbo_vertices);
      glVertexAttribPointer(
        mesh->attribute_v_coord,  // attribute
        4,                  // number of elements per vertex, here (x,y,z,w)
        GL_FLOAT,           // the type of each element
        GL_FALSE,           // take our values as-is
        0,                  // no extra data between each position
        0                   // offset of first element
      );

      glEnableVertexAttribArray(mesh->attribute_v_uv);
      glBindBuffer(GL_ARRAY_BUFFER, mesh->m_vbo_uvs);
      glVertexAttribPointer(
        mesh->attribute_v_uv, // attribute
        2,                  // number of elements per vertex, here (x,y,z)
        GL_FLOAT,           // the type of each element
        GL_FALSE,           // take our values as-is
        0,                  // no extra data between each position
        0                   // offset of first element
      );

      // glEnableVertexAttribArray(mesh->attribute_v_normal);
      // glBindBuffer(GL_ARRAY_BUFFER, mesh->m_vbo_normals);
      // glVertexAttribPointer(
      //   mesh->attribute_v_normal, // attribute
      //   3,                  // number of elements per vertex, here (x,y,z)
      //   GL_FLOAT,           // the type of each element
      //   GL_FALSE,           // take our values as-is
      //   0,                  // no extra data between each position
      //   0                   // offset of first element
      // );


      if (mesh->texture)
      {
        mesh->texture->bind();
      }
      else
      {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, 0);
      }




      for (auto const transforms : meshes.second)
      {
        //std::cout << "Transforms " << std::endl;
        // Set the local transform matrix

        glUniformMatrix4fv(uniformMVP, 1, GL_FALSE, &transforms[0][0]);

        // Draw Elements
        for (auto const elements : mesh->m_matIboElements)
        {
          //std::cout << "Wlwmwnts " << std::endl;

          glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elements.second);
          int size = mesh->m_matElements[elements.first].size(); // TODO what?
          //int size = elements.second.size();
          // setRenderColour(c, uniformDiffuse);
          // c++;
          //std::cout << size << std::endl;

          // Should be setting colour and texture uniforms
          float colour[] = {1.f, 1.f, 1.f };
          glUniform3fv(uniformDiffuse, 1, colour);

          //
          //              ----     DRAW     ----
          //
          glDrawElements(GL_TRIANGLES, size, GL_UNSIGNED_SHORT, 0);

          //std::cout << size << std::endl;
          //std::cout << "Drawing " << std::endl;
        }
      }
    }
  }
}
