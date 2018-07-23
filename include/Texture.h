#include "graphics.h"


class Texture
{
public:
  Texture();
  ~Texture();

  void loadRaw(const char* file);
  void loadPng(const char* file);

  void bind();

protected:

  GLuint m_texture = 0;
};
