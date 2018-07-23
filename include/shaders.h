#ifndef SHADERS_H
#define SHADERS_H

#include "graphics.h"

GLuint loadShader(GLenum type, const char *source);
GLuint buildProgram(GLuint vertexShader, GLuint fragmentShader,
  const char * vertexPositionName, const char * vertexNormalName);

#endif
