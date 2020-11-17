#include "Mesh_obj.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <iterator>


//
// Obj loading
//
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


Mesh_obj::Mesh_obj()
{

}


Mesh_obj::~Mesh_obj()
{
}


void Mesh_obj::load_obj(const char* filename)
{
  using namespace std;

  ifstream in(filename, ios::in);
  if (!in)
  {
      cout << "Cannot open " << filename << endl;
      cerr << "Cannot open " << filename << endl; exit(1);
  }
  load_stream(in);
}


void Mesh_obj::load_stream(std::istream& in)
{
  using namespace std;
 
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
          s >> v.y;
          s >> v.z;
          s >> v.x;
          v.x = -v.x;
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
          //cout << m_active << endl;
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

  //cout << "loaded " << m_obj_vertices.size() << " vertices." << endl;
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


int Mesh_obj::addUniqueVertex(std::string& vertexString)
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


void Mesh_obj::load_obj_data(const char* data, unsigned int size)
{
  std::string s(data, size);
  std::istringstream mb(s);
  load_stream(mb);
}
