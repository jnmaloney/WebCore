#include "RenderSystem.h"
#include "shaders.h"
#include "Mesh.h"
#include <iostream>


RenderSystem::RenderSystem()
{
}


void RenderSystem::init(WindowManager& window)
{
  // Assign vars
  m_window = window;

  // GL Setup
  glEnable(GL_DEPTH_TEST);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable( GL_BLEND );

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

   // Shaders

	const char vertexShaderSource[] =
		"attribute vec4 vPosition;		                     \n"
    "attribute vec2 vUV; \n"
    "uniform mat4 ModelLocal; \n"
    "uniform mat4 ViewProj; \n"
    "varying vec2 uv;                                 \n"
		"void main()                                         \n"
		"{                                                   \n"
    "   gl_Position = ViewProj * (ModelLocal * vPosition);                         \n"
//		"   gl_Position = (ModelLocal * vPosition);                         \n"
    "   uv.x = vUV.x; \n"
    "   uv.y = vUV.y; \n"
		"}                                                   \n";

  const char fragmentShaderSource[] =
		"precision mediump float;                     \n"
    "uniform sampler2D BaseMap;									\n"
    "varying vec2 uv;                                 \n"
		"void main()                                  \n"
		"{                                            \n"
    "  gl_FragColor = texture2D(BaseMap, uv); \n"
//    "  gl_FragColor = vec4(uv.x, uv.y, 1.0, 1.0); \n"
		"}                      \n";


	//load vertex and fragment shaders
	GLuint vertexShader = loadShader(GL_VERTEX_SHADER, vertexShaderSource);
	GLuint fragmentShader = loadShader(GL_FRAGMENT_SHADER, fragmentShaderSource);
	programObject = buildProgram(vertexShader, fragmentShader, "vPosition", "vUV");

  attribute_v_coord = glGetAttribLocation(programObject, "vPosition");
  attribute_v_uv = glGetAttribLocation(programObject, "vUV");

  //std::cout << attribute_v_uv << std::endl;

  // Tex
  GLint texLoc;
  texLoc = glGetUniformLocation(programObject, "BaseMap");

	//save location of uniform variables
  uniformVP = glGetUniformLocation(programObject, "ViewProj");
  uniformML = glGetUniformLocation(programObject, "ModelLocal");
}


RenderSystem::~RenderSystem()
{


}


void RenderSystem::zoom(int i)
{
}


void RenderSystem::move(double x, double y)
{

}


void setCameraPos(float x, float y, float z)
{

}


void RenderSystem::setViewSettings(double hfov, double near, double far)
{

}


void RenderSystem::start()
{
  //glClearColor(0.f, 92.f / 255.f, 159.f / 255.f, 1.f); // "Skydiver"
  //glClearColor(142.0/255.0, 47.0/255.0, 21.0/255.0, 1.0); // "Autumn"
  //glViewport(0, 0, m_window.width, m_window.height);
  glClear( GL_COLOR_BUFFER_BIT );

  glDepthFunc(GL_LESS);

  glm::mat4 VP(1.0);
}


void RenderSystem::modePersp()
{
  glm::mat4 VP(1.0);
  VP = glm::perspective( 15.f, 640.f / 576.f, 0.1f, 10.f );

  glUseProgram(programObject);
  glUniformMatrix4fv(uniformVP, 1, GL_FALSE, &VP[0][0]);
}


void RenderSystem::modeOrtho()
{
  glm::mat4 VP(1.0);
  VP = glm::ortho( 0.f, 1.f, 1.f, 0.f, -10.f, 10.f );

  glUseProgram(programObject);
  glUniformMatrix4fv(uniformVP, 1, GL_FALSE, &VP[0][0]);
}


void RenderSystem::modeOrtho(float x, float y)
{
  glm::mat4 VP(1.0);
  VP = glm::ortho( 0.f, x, y, 0.f, -10.f, 10.f );

  glUseProgram(programObject);
  glUniformMatrix4fv(uniformVP, 1, GL_FALSE, &VP[0][0]);
}


void RenderSystem::modeOrtho(float x, float y, float w, float h)
{
  glm::mat4 VP(1.0);
  VP = glm::ortho( x, x+w, y+h, y, -10.f, 10.f );

  glUseProgram(programObject);
  glUniformMatrix4fv(uniformVP, 1, GL_FALSE, &VP[0][0]);
}


void RenderSystem::end()
{
  glUseProgram(programObject);
}


void RenderSystem::setCursor(int x, int y)
{

}


bool RenderSystem::enableVertexPos(GLint program)
{
  if (program == programObject)
  {
      glEnableVertexAttribArray(attribute_v_coord);
      return true;
  }

  return false;
}


bool RenderSystem::enableVertexUV(GLint program)
{
  if (program == programObject)
  {
      glEnableVertexAttribArray(attribute_v_uv);
      return true;
  }

  return false;
}
