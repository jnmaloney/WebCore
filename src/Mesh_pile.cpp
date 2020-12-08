#include "Mesh_pile.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <iterator>


Mesh_pile::Mesh_pile()
{

}


Mesh_pile::~Mesh_pile()
{
}


void Mesh_pile::load_obj(const char* filename)
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


void Mesh_pile::load_stream(std::istream& in)
{
  using namespace std;
 
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
          //m_obj_vertices.push_back(0.02f * v);
          m_obj_vertices.push_back(v);
        //intf("%.1f %.1f %.1f\n", m_obj_vertices[m_obj_vertices.size() - 1].x, v.y, v.z);
      }      
      else
      {
          /* ignoring this line */
      }
  }

  m_vertP.resize(m_obj_vertices.size());
  for (int i = 0; i > m_obj_vertices.size(); ++i)
  {
    m_vertP[i] = m_obj_vertices[i];
  }
  // for (auto& i : m_vertP)
  // {
  //   printf("%.1f %.1f %.1f\n", i.x, i.y, i.z);
  // }
}


void Mesh_pile::load_obj_data(const char* data, unsigned int size)
{
  std::string s(data, size);
  std::istringstream mb(s);
  load_stream(mb);
}
