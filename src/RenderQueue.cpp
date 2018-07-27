#include "RenderQueue.h"
#include "Mesh.h"
#include <iostream>
#include "Texture.h"
#include "RenderSystem.h"


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

  m_currentTransform.setDiffuse = false;
  m_currentTransform.setPallette = false;
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


void RenderQueue::setDiffuse(glm::vec3 d)
{
  m_currentTransform.setDiffuse = true;
  m_currentTransform.diffuse = d;
}


void RenderQueue::setPallette(std::vector<int> p)
{
  m_currentTransform.setPallette = true;
  m_currentTransform.pallette_id = p;
}


void RenderQueue::setMVP(glm::mat4 mvp)
{
  //std::cout << "Set MVP " << m_currentTransformLevel->size() << std::endl;
  m_currentTransform.x = mvp;
  m_currentTransformLevel->push_back(m_currentTransform);
  //std::cout << "Set MVP " << m_currentTransformLevel->size() << std::endl;
}


void RenderQueue::submit()
{
  // Add elements to ElementLevel
}


void RenderQueue::draw(GLint a0, GLint a1, RenderSystem* rs)
{
  //std::cout << "draw() " << m_programs.size() << std::endl;

  for (auto const programs : m_programs )
  {
    glUseProgram(programs.first);

    for (auto const meshes : programs.second )
    {
      // Bind the mesh verts

      Mesh* mesh = meshes.first;

      //glEnableVertexAttribArray(mesh->attribute_v_coord);
      if (rs->enableVertexPos(programs.first))
      {
        // Describe our vertices array to OpenGL (it can't guess its format automatically)
        glBindBuffer(GL_ARRAY_BUFFER, mesh->m_vbo_vertices);
        glVertexAttribPointer(
          rs->att,  // attribute
          4,                  // number of elements per vertex, here (x,y,z,w)
          GL_FLOAT,           // the type of each element
          GL_FALSE,           // take our values as-is
          0,                  // no extra data between each position
          0                   // offset of first element
        );
      }

      //glEnableVertexAttribArray(mesh->attribute_v_uv);
      if (rs->enableVertexUV(programs.first))
      {
        glBindBuffer(GL_ARRAY_BUFFER, mesh->m_vbo_uvs);
        glVertexAttribPointer(
          rs->att, // attribute
          2,                  // number of elements per vertex, here (x,y,z)
          GL_FLOAT,           // the type of each element
          GL_FALSE,           // take our values as-is
          0,                  // no extra data between each position
          0                   // offset of first element
        );
      }

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
        // Set the local transform matrix

        glUniformMatrix4fv(rs->uniformML, 1, GL_FALSE, &transforms.x[0][0]);
        glUniformMatrix4fv(rs->uniformML2, 1, GL_FALSE, &transforms.x[0][0]);

        // Draw Elements
        for (auto const elements : mesh->m_matIboElements)
        {
          // Render the element
          // - Calculate the size of the element (TODO)
          // - Set uniforms (colour)
          // - Draw

          glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elements.second.elements);
          //int size = mesh->m_matElements[elements.first].size(); // TODO what?
          //int size = elements.second.size();
          // setRenderColour(c, uniformDiffuse);
          // c++;
          //std::cout << size << std::endl;

          // Should be setting colour and texture uniforms
          float colour[] = {1.f, 1.f, 1.f };

          if (transforms.setDiffuse)
          {
            colour[0] = transforms.diffuse.x;
            colour[1] = transforms.diffuse.y;
            colour[2] = transforms.diffuse.z;
          }
          else if (transforms.setPallette)
          {
            int i = transforms.pallette_id[elements.second.index];
            colour[0] = mesh->pallette->colours[i].x;
            colour[1] = mesh->pallette->colours[i].y;
            colour[2] = mesh->pallette->colours[i].z;
          }
          else if (mesh->pallette)
          {
            int i = elements.second.index % mesh->pallette->colours.size();
            colour[0] = mesh->pallette->colours[i].x;
            colour[1] = mesh->pallette->colours[i].y;
            colour[2] = mesh->pallette->colours[i].z;
          }

          glUniform3fv(rs->uniformDiffuse, 1, colour);
          glUniform3fv(rs->uniformDiffuse2, 1, colour);

          //
          //              ----     DRAW     ----
          //
          glDrawElements(GL_TRIANGLES, elements.second.size, GL_UNSIGNED_SHORT, 0);

          //std::cout << size << std::endl;
          //std::cout << "Drawing " << std::endl;
        }
      }
    }
  }
}
