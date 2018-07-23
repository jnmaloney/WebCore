#include "Mesh.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <iterator>


template<typename Out>
void split(const std::string &s, char delim, Out result) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        *(result++) = item;
    }
}

std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, std::back_inserter(elems));
    return elems;
}


GLuint Mesh::attribute_v_normal = -1;
GLuint Mesh::attribute_v_coord = -1;
GLuint Mesh::attribute_v_uv = -1;


Mesh::Mesh()
{

}


Mesh::~Mesh()
{

}


void Mesh::load_obj(const char* filename)
{
  using namespace std;

  ifstream in(filename, ios::in);
  if (!in)
  {
      cout << "Cannot open " << filename << endl;
      cerr << "Cannot open " << filename << endl; exit(1);
  }

  cout << "opened " << filename << endl;

  std::vector<glm::vec3>& load_normals = m_obj_normals;
  std::vector<glm::vec2>& load_uvs = m_obj_uvs;

  string line;
  while (getline(in, line))
  {
      //cout << line << endl;
      if (line.substr(0,2) == "v ")
      {
          istringstream s(line.substr(2));
          glm::vec4 v;
          s >> v.x;
          s >> v.z;
          s >> v.y;
          v.w = 1.0f;
          m_obj_vertices.push_back(0.02f * v);
      }
      else if (line.substr(0,2) == "vn") // normals
      {
        istringstream s(line.substr(2));
        glm::vec3 v;
        s >> v.x;
        s >> v.z;
        s >> v.y;
        load_normals.push_back(v);
      }
      else if (line.substr(0,2) == "vt") // uvs
      {
        istringstream s(line.substr(2));
        glm::vec2 v;
        s >> v.x;
        s >> v.y;
        v.y = 1.0 - v.y;
        load_uvs.push_back(v);
      }
      else if (line.substr(0,2) == "f ")
      {
          istringstream s(line.substr(2));

          // Faces with normals
          std::string but;
          for (int i = 0; i < 3; ++i) // HACK Force tri
          {
            s >> but;

            // Add uniqueVertex to vertex set
            int index = addUniqueVertex(but);
            // Note index of uniqueVertex for face
            m_matElements[m_active].push_back(index);
          }

      }
      else if (line.substr(0,2) == "o ")
      {
        load_normals.resize(0);
        load_uvs.resize(0);
      }
      else if (line.substr(0,7) == "usemtl ")
      {
          istringstream s(line.substr(7));
          s >> m_active;
          cout << m_active << endl;
      }
      // else if (line.substr(0,2) == "s ")
      // {
      //     istringstream s(line.substr(2));
      //     s >> m_active;
      //     cout << m_active << endl;
      // }
      else if (line[0] == '#')
      {

      }
      else
      {
          /* ignoring this line */
      }
  }

  cout << "loaded " << m_obj_vertices.size() << " vertices." << endl;
  //cout << "loaded " << m_obj_elements.size() << " elements." << endl;

  if (m_obj_uvs.size() == 0)
  {
    m_obj_uvs.resize(m_obj_vertices.size(), glm::vec3(0.0, 0.0, 0.0));
  }

  if (m_obj_normals.size() == 0)
  {
    m_obj_normals.resize(m_obj_vertices.size(), glm::vec3(0.0, 0.0, 1.0));
  }

  //
  // Generate, from the unique vertex set, a list of vertix properties
  // With position, normal and uv, all unique.
  // Have to split some vertices here
  //
  m_vertP.resize(m_uniqueVerts.size());
  m_vertN.resize(m_uniqueVerts.size());
  m_vertT.resize(m_uniqueVerts.size());
  for (int i = 0; i < m_uniqueVerts.size(); ++i)
  {
    std::string vertexString = m_uniqueVerts[i];

    // SPLITTING
    glm::vec4 vp = glm::vec4(0.f);
    glm::vec3 vn = glm::vec3(0.f);
    glm::vec2 vt = glm::vec2(0.f);
    std::vector<std::string> sp = split(vertexString, '/');

    if (sp.size() >= 1)
    {
      GLushort a;
      a = std::stoi( sp[0] ) - 1;
      vp = m_obj_vertices[a];
    }

    // a/B/c
    if (sp.size() >= 2)
    {
      GLushort a;
      a = std::stoi( sp[1] ) - 1;
      if (m_obj_uvs.size())
        vt = m_obj_uvs[a];
    }

    // a/b/C
    if (sp.size() >= 3)
    {
      GLushort a;
      a = std::stoi( sp[2] ) - 1;
      vn = m_obj_normals[a];
    }

    m_vertP[i] = vp;
    m_vertN[i] = vn;
    m_vertT[i] = vt;
  }

}


void Mesh::upload_obj()
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
  std::cout << m_vertN[0].x << " " << m_vertN[0].y << " " << m_vertN[0].z << std::endl;

  for (auto i = m_matElements.begin(); i != m_matElements.end(); ++i)
  {
    if ((*i).second.size() > 0)
    {
      GLuint ibo_elements;
      glGenBuffers(1, &ibo_elements);
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_elements);
      glBufferData(GL_ELEMENT_ARRAY_BUFFER,(*i).second.size() * sizeof((*i).second[0]),
        (*i).second.data(), GL_STATIC_DRAW); // elements (faces)

      m_matIboElements[(*i).first] = ibo_elements;

    } else std::cout << "no upload ele" << std::endl;
  }
}


void Mesh::drawWireframe(GLuint uniformDiffuse, int tag)
{
  if (m_matElements[m_active].size() == 0) return;

  glEnableVertexAttribArray(attribute_v_coord);
  // Describe our vertices array to OpenGL (it can't guess its format automatically)
  glBindBuffer(GL_ARRAY_BUFFER, m_vbo_vertices);
  glVertexAttribPointer(
    attribute_v_coord,  // attribute
    4,                  // number of elements per vertex, here (x,y,z,w)
    GL_FLOAT,           // the type of each element
    GL_FALSE,           // take our values as-is
    0,                  // no extra data between each position
    0                   // offset of first element
  );

  for (auto i = m_matIboElements.begin(); i != m_matIboElements.end(); ++i)
  {
     glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, (*i).second);
     int size = m_matElements[(*i).first].size();

     glDrawElements(GL_LINES, size, GL_UNSIGNED_SHORT, 0);
     //glDrawElements(GL_POINTS, size, GL_UNSIGNED_SHORT, 0);
  }

  glDisableVertexAttribArray(attribute_v_coord);
}


void Mesh::draw(GLuint uniformDiffuse)
{
  if (m_matElements[m_active].size() == 0) return;

  //
  // Draw
  //


  glEnableVertexAttribArray(attribute_v_coord);
  // Describe our vertices array to OpenGL (it can't guess its format automatically)
  glBindBuffer(GL_ARRAY_BUFFER, m_vbo_vertices);
  glVertexAttribPointer(
    attribute_v_coord,  // attribute
    4,                  // number of elements per vertex, here (x,y,z,w)
    GL_FLOAT,           // the type of each element
    GL_FALSE,           // take our values as-is
    0,                  // no extra data between each position
    0                   // offset of first element
  );

  glEnableVertexAttribArray(attribute_v_uv);
  glBindBuffer(GL_ARRAY_BUFFER, m_vbo_uvs);
  glVertexAttribPointer(
    attribute_v_uv, // attribute
    2,                  // number of elements per vertex, here (x,y,z)
    GL_FLOAT,           // the type of each element
    GL_FALSE,           // take our values as-is
    0,                  // no extra data between each position
    0                   // offset of first element
  );

  glEnableVertexAttribArray(attribute_v_normal);
  glBindBuffer(GL_ARRAY_BUFFER, m_vbo_normals);
  glVertexAttribPointer(
    attribute_v_normal, // attribute
    3,                  // number of elements per vertex, here (x,y,z)
    GL_FLOAT,           // the type of each element
    GL_FALSE,           // take our values as-is
    0,                  // no extra data between each position
    0                   // offset of first element
  );

  // if (m_ibo_elements == 0)
  // {
  //   glDrawArrays(GL_TRIANGLES, 0, m_obj_vertices.size());
  // }
  //else
  // {
  //  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo_elements);
  //  int size = m_matElements[m_active].size();
  //  //glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
  //  //std::cout << size << std::endl;
  //  //glDrawElements(GL_POINTS, size/sizeof(GLushort), GL_UNSIGNED_SHORT, 0);
  //  glDrawElements(GL_TRIANGLES, size, GL_UNSIGNED_SHORT, 0);
  //  //glDrawElements(GL_POINTS, size, GL_UNSIGNED_SHORT, 0);
  // }


  // //float colour0[] = { 58.f / 255.f, 121.f / 255.f,  94.f / 255.f }; // pine
  // float colour0[] = { 88.f / 255.f, 91.f / 255.f,  94.f / 255.f }; // paved
  // //float colour1[] = { 0.f / 255.f, 179.f / 255.f,  105.f / 255.f }; // Asph?
  // float colour1[] = { 160.f / 255.f, 169.f / 255.f,  155.f / 255.f }; // Asph?
  // float colour2[] = { 123.f / 255.f, 0.f / 255.f,  105.f / 255.f }; // Grass Green
  // float colour3[] = { 123.f / 255.f, 179.f / 255.f,  0.f / 255.f }; // Grass Green
  // float colour4[] = {1.f, 1.f, 1.f }; // Grass Green
  //
  int c = 0;
  for (auto i = m_matIboElements.begin(); i != m_matIboElements.end(); ++i)
  {
     glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, (*i).second);
     int size = m_matElements[(*i).first].size();
     //int size;
     //glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
     //std::cout << size << std::endl;
     //glDrawElements(GL_POINTS, size/sizeof(GLushort), GL_UNSIGNED_SHORT, 0);

          // if (c%5==0) glUniform3fv(uniformDiffuse, 1, colour0);
          // if (c%5==1) glUniform3fv(uniformDiffuse, 1, colour1);
          // if (c%5==2) glUniform3fv(uniformDiffuse, 1, colour2);
          // if (c%5==3) glUniform3fv(uniformDiffuse, 1, colour3);
          // if (c%5==4) glUniform3fv(uniformDiffuse, 1, colour4);

      setRenderColour(c++, uniformDiffuse);

     glDrawElements(GL_TRIANGLES, size, GL_UNSIGNED_SHORT, 0);
     //glDrawElements(GL_POINTS, size, GL_UNSIGNED_SHORT, 0);

  }

  glDisableVertexAttribArray(attribute_v_coord);
  //glDisableVertexAttribArray(1);


  // glEnableVertexAttribArray(0);
  // glBindBuffer(GL_ARRAY_BUFFER, m_vbo_vertices);
  // GLushort* ptr = 0;
  // glVertexAttribPointer(
  //    0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
  //    4,                  // size
  //    GL_FLOAT,           // type
  //    GL_FALSE,           // normalized?
  //    7*sizeof(GLushort),                  // stride
  //    (void*)(ptr+0)            // array buffer offset
  // );
  // glEnableVertexAttribArray(1);
  // glVertexAttribPointer(
  //    1,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
  //    3,                  // size
  //    GL_FLOAT,           // type
  //    GL_FALSE,           // normalized?
  //    7*sizeof(GLushort),                  // stride
  //    (void*)(ptr+4)            // array buffer offset
  // );
  // // Draw the triangle !
  // glDrawArrays(GL_TRIANGLES, 0, 6); // Starting from vertex 0; 3 vertices total -> 1 triangle
  // //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo_elements);
  // //glDrawElements(GL_TRIANGLES, 696/sizeof(GLushort), GL_UNSIGNED_SHORT, 0);
  // glDisableVertexAttribArray(0);
  // glDisableVertexAttribArray(1);
}


static glm::vec3 desaturate(glm::vec3 input)
{
  glm::vec3 output = glm::vec3(1.0);
  output[0] = input[0] * 0.5 + 0.4;
  output[1] = input[1] * 0.5 + 0.4;
  output[2] = input[2] * 0.5 + 0.4;
  return output;
}

void Mesh::setColourSceme(int i)
{
  m_colours.resize(0);
  m_colours.push_back(glm::vec3(88.f / 255.f, 91.f / 255.f,  94.f / 255.f));
  m_colours.push_back(glm::vec3(160.f / 255.f, 169.f / 255.f,  155.f / 255.f));
}


void Mesh::setRenderColour(int i, GLuint uniformDiffuse)
{
  float colour[] = {1.f, 1.f, 1.f };

  if (m_colours.size())
  {
    glm::vec3 col = m_colours[i % m_colours.size()];
    colour[0] = col[0];
    colour[1] = col[1];
    colour[2] = col[2];
  }

  glUniform3fv(uniformDiffuse, 1, colour);
}


void Mesh::draw_bbox()
{
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
/*

*/


void Mesh::beSquare()
{
  m_vertP.push_back(glm::vec4( 0.5f,  0.5f, 0.0f, 0.f));
  m_vertP.push_back(glm::vec4(-0.5f,  0.5f, 0.0f, 0.f));
  m_vertP.push_back(glm::vec4(-0.5f, -0.5f, 0.0f, 0.f));
  m_vertP.push_back(glm::vec4( 0.5f, -0.5f, 0.0f, 0.f));

  m_vertN.push_back(glm::vec3(0.f,  0.f, 1.0f));
  m_vertN.push_back(glm::vec3(0.f,  0.f, 1.0f));
  m_vertN.push_back(glm::vec3(0.f,  0.f, 1.0f));
  m_vertN.push_back(glm::vec3(0.f,  0.f, 1.0f));

  m_vertT.push_back(glm::vec2(1.f,  1.f));
  m_vertT.push_back(glm::vec2(0.f,  1.f));
  m_vertT.push_back(glm::vec2(0.f,  0.f));
  m_vertT.push_back(glm::vec2(1.f,  0.f));

  m_matElements[""].push_back(0);
  m_matElements[""].push_back(2);
  m_matElements[""].push_back(1);
  m_matElements[""].push_back(3);
  m_matElements[""].push_back(1);
  m_matElements[""].push_back(2);

  upload_obj();
}
