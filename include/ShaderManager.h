#pragma once


#include <map>


class RenderSystem;


class ShaderManager
{
public:
  ShaderManager();
  ~ShaderManager();

  // Loading
  //void addLoadShader(std::string id, std::string filename);
  void loadProgram(std::string id, std::string vert_file, std::string frag_file, int att = 0);
  void init();

  // Enable shader
  void setShader(std::string id);

  // Updates parameters from RenderSystem
  void update(RenderSystem* rs);

  // Get Attribute or Uniform value
  unsigned int getAttribute(std::string id);

  void setProgramVec3(glm::vec3& v);  

  void setParam(std::string id, std::string param, float value);

protected:


  std::map<std::string, unsigned int> m_shaderPrograms;

  typedef std::map<std::string, unsigned int> AttributeMap;
  std::map<unsigned int, AttributeMap> m_shaderAttributes;

  unsigned int m_currentProgram = 0;
};
