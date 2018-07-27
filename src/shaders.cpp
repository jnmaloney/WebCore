#include "shaders.h"
#include <iostream>

using namespace std;

GLuint loadShader(GLenum type, const char *source)
{
	//create a shader
	GLuint shader = glCreateShader(type);
	if (shader == 0)
	{
		cerr << "Error creating shader" << endl;
		return 0;
	}

	//load the shader source to the shader object and compile it
	glShaderSource(shader, 1, &source, NULL);
	glCompileShader(shader);

	//check if the shader compiled successfully
	GLint compiled;
	 GLint info_length = 0;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
	if (!compiled)
	{
		cerr << "Shader compilation error #" << shader << endl;

		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &info_length);
    if(info_length > 0) {
        char info_log[1024] = {0};
        glGetShaderInfoLog(shader, sizeof(info_log), NULL, info_log);
        cerr << "Info compiling " << shader << ":" << info_log;
		}

		glDeleteShader(shader);
		return 0;
	}
	else {
		cerr << "Shader complete #" << shader << endl;
	}

	return shader;
}

GLuint buildProgram(GLuint vertexShader, GLuint fragmentShader, const char * vertexPositionName, const char * vertexNormalName)
{
	//create a GL program and link it
	GLuint programObject = glCreateProgram();
	glAttachShader(programObject, vertexShader);
	glAttachShader(programObject, fragmentShader);
	glBindAttribLocation(programObject, 0, vertexPositionName);
	//glBindAttribLocation(programObject, 1, vertexNormalName); // add line
	if (vertexNormalName) glBindAttribLocation(programObject, 1, vertexNormalName); // add line
	glLinkProgram(programObject);

	//check if the program linked successfully
	GLint linked;
	glGetProgramiv(programObject, GL_LINK_STATUS, &linked);
	if (!linked)
	{
		cerr << "Program link error" << endl;
		glDeleteProgram(programObject);
		return 0;
	}
	return programObject;
}
