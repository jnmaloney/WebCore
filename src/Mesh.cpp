#include "Mesh.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <iterator>


Mesh::Mesh()
{

}


Mesh::~Mesh()
{

}


void Mesh::clear()
{
    if (m_vbo_vertices) glDeleteBuffers(1, &m_vbo_vertices);
    if (m_vbo_uvs) glDeleteBuffers(1, &m_vbo_uvs);
    if (m_vbo_normals) glDeleteBuffers(1, &m_vbo_normals);
    for (auto i : m_matIboElements)
      glDeleteBuffers(1, &i.second.elements);
}


int Mesh::addUniqueVertex(std::string& vertexString)
{
  std::vector<std::string>::iterator iter = std::find(
    m_uniqueVerts.begin(),
    m_uniqueVerts.end(),
    vertexString);
  size_t index = std::distance(
    m_uniqueVerts.begin(),
    iter);
  if(index == m_uniqueVerts.size())
  {
      //invalid
      m_uniqueVerts.push_back(vertexString);
      return m_uniqueVerts.size() - 1;
  }
  else return index;

}


// void Mesh::beSquare()
// {
//   m_vertP.push_back(glm::vec4( 0.5f,  0.5f, 0.0f, 0.f));
//   m_vertP.push_back(glm::vec4(-0.5f,  0.5f, 0.0f, 0.f));
//   m_vertP.push_back(glm::vec4(-0.5f, -0.5f, 0.0f, 0.f));
//   m_vertP.push_back(glm::vec4( 0.5f, -0.5f, 0.0f, 0.f));

//   m_vertN.push_back(glm::vec3(0.f,  0.f, 1.0f));
//   m_vertN.push_back(glm::vec3(0.f,  0.f, 1.0f));
//   m_vertN.push_back(glm::vec3(0.f,  0.f, 1.0f));
//   m_vertN.push_back(glm::vec3(0.f,  0.f, 1.0f));

//   m_vertT.push_back(glm::vec2(1.f,  1.f));
//   m_vertT.push_back(glm::vec2(0.f,  1.f));
//   m_vertT.push_back(glm::vec2(0.f,  0.f));
//   m_vertT.push_back(glm::vec2(1.f,  0.f));

//   m_matElements[""].push_back(0);
//   m_matElements[""].push_back(2);
//   m_matElements[""].push_back(1);
//   m_matElements[""].push_back(3);
//   m_matElements[""].push_back(1);
//   m_matElements[""].push_back(2);

//   upload();
// }


void Mesh::upload()
{
  //
  // Upload
  //
  if (m_vertP.size() > 0)
  {
    glGenBuffers(1, &m_vbo_vertices);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo_vertices);
    glBufferData(GL_ARRAY_BUFFER,
      m_vertP.size() * sizeof(m_vertP[0]),
      m_vertP.data(), GL_STATIC_DRAW);
  } else std::cout << "no upload vert" << std::endl;

  if (m_vertT.size() > 0)
  {
    glGenBuffers(1, &m_vbo_uvs);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo_uvs);
    glBufferData(GL_ARRAY_BUFFER,
      m_vertT.size() * sizeof(m_vertT[0]),
      m_vertT.data(), GL_STATIC_DRAW);
  } else std::cout << "no upload uvs" << std::endl;

  if (m_vertN.size() > 0)
  {
    glGenBuffers(1, &m_vbo_normals);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo_normals);
    glBufferData(GL_ARRAY_BUFFER,
      m_vertN.size() * sizeof(m_vertN[0]),
      m_vertN.data(), GL_STATIC_DRAW);
  } else std::cout << "no upload nor" << std::endl;

  for (auto i = m_matElements.begin(); i != m_matElements.end(); ++i)
  {
    if ((*i).second.size() > 0)
    {
      GLuint ibo_elements;
      glGenBuffers(1, &ibo_elements);
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_elements);
      glBufferData(GL_ELEMENT_ARRAY_BUFFER,(*i).second.size() * sizeof((*i).second[0]),
        (*i).second.data(), GL_STATIC_DRAW); // elements (faces)

      Mesh::IboElement iboel;
      iboel.name = (*i).first;
      iboel.index = m_matIboElements.size();
      iboel.size = m_matElements[(*i).first].size();
      iboel.size = m_matElements[(*i).first].size();
      iboel.elements = ibo_elements;
      m_matIboElements[iboel.index] = iboel;

    } else std::cout << "no upload ele" << std::endl;
  }
}

