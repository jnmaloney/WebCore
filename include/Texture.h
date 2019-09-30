#pragma once


#include "graphics.h"


class TileSet;


class Texture
{
public:
  Texture();
  ~Texture();

  void loadRaw(const char* file);
  void loadPng(const char* file);
  void loadPng_withCollisionShapes(const char* file, TileSet* tileset);

  void bind();

  int mWidth = 0;
  int mHeight = 0;

  GLuint getID() { return m_texture; }

protected:

  GLuint m_texture = 0;
};
