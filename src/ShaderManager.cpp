#include "RenderSystem.h"
#include "ShaderManager.h"
#include "shaders.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>


ShaderManager::ShaderManager()
{

}


ShaderManager::~ShaderManager()
{
}


// void ShaderManager::addLoadShader(std::string id, std::string filename)
// {
//   std::ifstream in(filename, ios::in);
//   std::string str((std::istreambuf_iterator<char>(in)),
//                  std::istreambuf_iterator<char>());
//
//   // GLuint vertexShader = loadShader(GL_VERTEX_SHADER, str.c_str());
//  	// GLuint fragmentShader = loadShader(GL_FRAGMENT_SHADER, str.c_str());
//   //
//   // programObject = buildProgram(vertexShader, fragmentShader, "vPosition", "vUV");
// }


void ShaderManager::loadProgram(std::string id, std::string vert_file, std::string frag_file, int att)
{
  GLuint vertexShader = 0;
  GLuint fragmentShader = 0;

  // Vert
  {
    std::ifstream in(vert_file, std::ios::in);
    std::string str((std::istreambuf_iterator<char>(in)),
                   std::istreambuf_iterator<char>());

    vertexShader = loadShader(GL_VERTEX_SHADER, str.c_str());
  }

  // Frag
  {
    std::ifstream in(frag_file, std::ios::in);
    std::string str((std::istreambuf_iterator<char>(in)),
                   std::istreambuf_iterator<char>());

    fragmentShader = loadShader(GL_FRAGMENT_SHADER, str.c_str());
  }

  GLuint programObject = buildProgram(vertexShader, fragmentShader, "vPosition", "vUV");

  // Save compiled program
  m_shaderPrograms[id] = programObject;

  // Attributes / Uniforms
  // TODO
  GLuint attribute_v_coord = glGetAttribLocation(programObject, "vPosition");
  GLuint attribute_v_uv = glGetAttribLocation(programObject, "vUV");
  GLuint uniformTex1 = glGetUniformLocation(programObject, "BaseMap");
  GLuint uniformML = glGetUniformLocation(programObject, "ModelLocal");
  GLuint uniformVP = glGetUniformLocation(programObject, "ViewProj");

  m_shaderAttributes[programObject]["attribute_v_coord"] = attribute_v_coord;
  m_shaderAttributes[programObject]["attribute_v_uv"] = attribute_v_uv;
  m_shaderAttributes[programObject]["uniformTex1"] = uniformTex1;
  m_shaderAttributes[programObject]["uniformML"] = uniformML;
  m_shaderAttributes[programObject]["uniformVP"] = uniformVP;

  // This is optional
  m_shaderAttributes[programObject]["uniformDiffuse"] = glGetUniformLocation(programObject, "diffuse");



  m_currentProgram = programObject;
  glUseProgram(m_currentProgram);
}


void ShaderManager::init()
{
}


void ShaderManager::setShader(std::string id)
{
  m_currentProgram = m_shaderPrograms[id];
  glUseProgram(m_currentProgram);
}


void ShaderManager::update(RenderSystem* rs)
{
  // Current program object has uniforms... wants values
  glUniformMatrix4fv(
    m_shaderAttributes[m_currentProgram]["uniformVP"],
    1,
    GL_FALSE,
    rs->getViewProj());
}


unsigned int ShaderManager::getAttribute(std::string id)
{
  return m_shaderAttributes[m_currentProgram][id];
}


void ShaderManager::setProgramVec3(glm::vec3& v)
{
  static unsigned int uni = m_shaderAttributes[m_currentProgram]["uniformDiffuse"]; // TODO
  glUniform3fv(
    uni,
    1,
    &v[0]);
}
