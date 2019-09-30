#include "Texture.h"
#include <fstream>
#include <vector>
#include <iostream>
#include "PngLoader.h"
#include "PngUtils.h"


Texture::Texture()
{

}


Texture::~Texture()
{

}


void Texture::loadPng_withCollisionShapes(const char* file, TileSet* tileset)
{
  PngLoader loader;
  loader.load(file);
  PngUtils pngu;
  pngu.prepareCollisionShapes(&loader, tileset);

  glActiveTexture(GL_TEXTURE1);

  glGenTextures(1, &m_texture);

  glBindTexture(GL_TEXTURE_2D, m_texture);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

  // TODO GL_RGBA format to match PNG format
  glTexImage2D(
    GL_TEXTURE_2D,
    0,
    GL_RGBA,
    loader.image.width,
    loader.image.height,
    0,
    GL_RGBA,
    GL_UNSIGNED_BYTE,
    loader.buffer);

  glGenerateMipmap(GL_TEXTURE_2D);

  glBindTexture(GL_TEXTURE_2D, m_texture);
}


void Texture::loadPng_fromMemory(const char* data, uint64_t numBytes)
{
  if (m_texture)
  {
    glGenTextures(1, &m_texture);    
  }

  PngLoader loader;
  loader.load_mem(data, numBytes);

  glActiveTexture(GL_TEXTURE1);

  glGenTextures(1, &m_texture);

  glBindTexture(GL_TEXTURE_2D, m_texture);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

  // TODO GL_RGBA format to match PNG format
  glTexImage2D(
    GL_TEXTURE_2D,
    0,
    GL_RGBA,
    loader.image.width,
    loader.image.height,
    0,
    GL_RGBA,
    GL_UNSIGNED_BYTE,
    loader.buffer);

  glGenerateMipmap(GL_TEXTURE_2D);

  glBindTexture(GL_TEXTURE_2D, m_texture);

  mWidth = loader.image.width;
  mHeight = loader.image.height;
}


void Texture::loadPng(const char* file)
{
  PngLoader loader;
  loader.load(file);

  glActiveTexture(GL_TEXTURE1);

  glGenTextures(1, &m_texture);

  glBindTexture(GL_TEXTURE_2D, m_texture);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

  // TODO GL_RGBA format to match PNG format
  glTexImage2D(
    GL_TEXTURE_2D,
    0,
    GL_RGBA,
    loader.image.width,
    loader.image.height,
    0,
    GL_RGBA,
    GL_UNSIGNED_BYTE,
    loader.buffer);

  glGenerateMipmap(GL_TEXTURE_2D);

  glBindTexture(GL_TEXTURE_2D, m_texture);

  mWidth = loader.image.width;
  mHeight = loader.image.height;
}


void Texture::loadRaw(const char* file)
{
  std::ifstream input( file, std::ios::binary );
  // copies all data into buffer
  std::vector<char> buffer((
        std::istreambuf_iterator<char>(input)),
        (std::istreambuf_iterator<char>()));

  glActiveTexture(GL_TEXTURE1);

  glGenTextures(1, &m_texture);

  glBindTexture(GL_TEXTURE_2D, m_texture);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 512, 512, 0, GL_RGB, GL_UNSIGNED_BYTE, buffer.data());

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

  glGenerateMipmap(GL_TEXTURE_2D);

  glBindTexture(GL_TEXTURE_2D, m_texture);

  std::cout << "Texture: " << m_texture << std::endl;
}


void Texture::bind()
{
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, m_texture);
}
