#pragma once


// #include "Singleton.h"
#include <map>
#include <string>


class Mesh;
void inspect(Mesh* mesh);


// Async resource file loader
class ResourceManager 
{
public:
  enum RESOURCE_TYPE
  {
    PNG = 0,
    OBJ,
    PILE,
    OGG
  };
  
  ResourceManager();
  ~ResourceManager();

  void addResource(const char* resource_name, const char* file_path, RESOURCE_TYPE resource_type);

  void start_async_load();

  bool getResource(const char* resource_name, unsigned int& resource_handle);
  //bool getResource(const char* resource_name, void*& resource_handle);
  bool getResource(const char* resource_name, void** resource_handle);
  
  //void unloadResource(..);


protected:

  struct Resource
  {
    std::string source_path;
    int loading_status = 0;
    RESOURCE_TYPE resource_type;
    unsigned int handle = 0;
  };

  std::map<std::string, Resource> m_resources;

  static void f_onload(void* arg, void* buffer, int size);
  static void f_onerr(void* arg);

};
