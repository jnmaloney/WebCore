#include "Mesh.h"
#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"
#include <iostream>
// #include <fstream>
// #include <string>
// #include <sstream>
// #include <vector>
// #include <iterator>
#include "RenderSystem.h"


struct MeshDef
{
  tinyobj::attrib_t attrib;
  std::vector<tinyobj::shape_t> shapes;
  std::vector<tinyobj::material_t> materials;
};


Mesh::Mesh()
{
  m_def = new MeshDef;
}


Mesh::~Mesh()
{
  delete m_def;
}


void Mesh::load_obj(const char* filename)
{
  // tinyobj::attrib_t attrib;
  // std::vector<tinyobj::shape_t> shapes;
  // std::vector<tinyobj::material_t> materials;
  std::string warn;
  std::string err;
  char* basepath = NULL;
  bool triangulate = false;
  bool ret = tinyobj::LoadObj(&m_def->attrib, &m_def->shapes, &m_def->materials,
                              &warn, &err, filename, basepath, triangulate);

  std::cout << ret << " " << m_def->attrib.vertices.size() << " " << m_def->shapes.size() << std::endl;
  std::cout << warn << std::endl;
  std::cout << err << std::endl;
}


// std::vector<float> getSub(std::vector<float>& input, int offset, int length, int stride)
// {
//   std::vector<float> r;
//   int i = 0;
//   while (i < input.size())
//   {
//     for (int j = i + offset; j < i + offset + length; ++j)
//     {
//       r.push_back(input[j]);
//     }
//     i += stride;
//   }
//   return r;
// }
std::vector<int> getSub(std::vector<tinyobj::index_t>& input)
{
  std::vector<int> r;
  r.resize(input.size());
  for (int i = 0; i < input.size(); ++i)
  {
    r[i] = input[i].vertex_index;
    //r[i] = input[i].texcoord_index;
  }
  return r;
}


void Mesh::upload_obj()
{
  // o.numTriangles = buffer.size() / (3 + 3 + 3 + 2) /
  //                  3;  // 3:vtx, 3:normal, 3:col, 2:texcoord

  //
  // Upload
  //
  //if (m_def->attrib.vertices.size() > 0)
  {
    glGenBuffers(1, &m_vbo_vertices);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo_vertices);
    //auto v = getSub(m_def->attrib.vertices, 0, 3, 11);
    auto v0 = m_def->attrib.vertices;
    std::vector<float> v;
    for (int i = 0; i < v0.size(); i += 3)
    {
      v.push_back(-v0[i+2]);
      v.push_back(v0[i+0]);
      v.push_back(v0[i+1]);
      v.push_back(1);
    }
    glBufferData(GL_ARRAY_BUFFER,
      v.size() * sizeof(v[0]),
      v.data(), GL_STATIC_DRAW);
      // for (auto i : v)
      //   std::cout << i << ", ";
      // std::cout << std::endl;
  } //else std::cout << "no upload vert" << std::endl;

  //if (m_vertT.size() > 0)
  {
    glGenBuffers(1, &m_vbo_uvs);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo_uvs);
    //auto v = getSub(m_def->attrib.vertices, 6, 3, 11);
    auto v = m_def->attrib.texcoords;
    glBufferData(GL_ARRAY_BUFFER,
      v.size() * sizeof(v[0]),
      v.data(), GL_STATIC_DRAW);
  } //else std::cout << "no upload uvs" << std::endl;

  // if (m_vertN.size() > 0)
  // {
  //   glGenBuffers(1, &m_vbo_normals);
  //   glBindBuffer(GL_ARRAY_BUFFER, m_vbo_normals);
  //   glBufferData(GL_ARRAY_BUFFER,
  //     m_vertN.size() * sizeof(m_vertN[0]),
  //     m_vertN.data(), GL_STATIC_DRAW);
  // } else std::cout << "no upload nor" << std::endl;
  //std::cout << m_vertN[0].x << " " << m_vertN[0].y << " " << m_vertN[0].z << std::endl;

  if (m_matIboElements.size() == m_def->shapes.size()) return; // check

  for (auto i = m_def->shapes.begin(); i != m_def->shapes.end(); ++i)
  {
    if ((*i).mesh.indices.size() > 0)
    {
      GLuint ibo_elements;
      glGenBuffers(1, &ibo_elements);
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_elements);
      auto v = getSub((*i).mesh.indices);
      glBufferData(GL_ELEMENT_ARRAY_BUFFER,
        v.size() * sizeof(int),
        v.data(),
        GL_STATIC_DRAW); // elements (faces)

      //m_matIboElements[(*i).first] = ibo_elements;
      Mesh::IboElement iboel;
      iboel.name = (*i).name;
      iboel.index = m_matIboElements.size();
      iboel.size = v.size();
      iboel.elements = ibo_elements;
      m_matIboElements[iboel.index] = iboel;

      //std::cout << (*i).name << " " << (*i).mesh.indices.size() << std::endl;
      std::cout << (*i).name << " " << v.size() << std::endl;
      for (int j = 0; j < v.size(); ++j)
        std::cout << v[j] << ", ";
      std::cout << std::endl;

    } else std::cout << "no upload ele" << std::endl;
  }
}


void Mesh::drawWireframe(GLuint uniformDiffuse, int tag)
{
}


void Mesh::bind(RenderSystem* rs)
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

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_matIboElements[0].elements);
}


void Mesh::draw()
{
  // glEnableClientState(GL_VERTEX_ARRAY);
  // glEnableClientState(GL_NORMAL_ARRAY);
  // glEnableClientState(GL_COLOR_ARRAY);
  // glEnableClientState(GL_TEXTURE_COORD_ARRAY);

  //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);
  glDrawElements(GL_TRIANGLES, m_matIboElements[0].size, GL_UNSIGNED_SHORT, 0);
}


void Mesh::draw_bbox()
{
}


int Mesh::encodeVert(int v, int t, int n)
{
  int s = m_def->vertices.size();
  return v + t * s + n * s * s;
}


void Mesh::decodeVert(int i, int& v, int& t, int& s)
{
  int s = m_def->vertices.size();
  v = i % s;
  t = ((i - v) / s) % s;
  n = (i - t * s - v) / s;
}
