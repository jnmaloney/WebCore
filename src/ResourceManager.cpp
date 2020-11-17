#include "ResourceManager.h"
#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif
#include <stdio.h>
#include "Texture.h"
#include "Mesh_obj.h"


void ResourceManager::f_onload(void* arg, void* buffer, int size)
{
  Resource* r = (Resource*)arg;

  //printf("Resource %s has finished loading with %i bytes.\n", r->source_path.c_str(), size);

  if (r->resource_type == PNG)
  {
    Texture* t = new Texture();
    t->loadPng_fromMemory((const char*)buffer, size);
    r->handle = t->getID();
    r->loading_status = 100;
    // TODO t leaks
  }
  else if (r->resource_type == OBJ)
  {
    Mesh_obj* mesh = new Mesh_obj;
    mesh->load_obj_data((const char*)buffer, size);
    mesh->upload();
    r->handle = (unsigned int)mesh;
  }
}


void ResourceManager::f_onerr(void* arg)
{
  Resource* r = (Resource*)arg;

  printf("Resource %s could not be loaded.\n", r->source_path.c_str());
}


ResourceManager::ResourceManager()
{

}


ResourceManager::~ResourceManager()
{

}


void ResourceManager::addResource(const char* resource_name, const char* file_path, RESOURCE_TYPE resource_type)
{
  // Check if exitsts
  if (m_resources.count(resource_name) > 0) 
  {
    printf("A resource with that name already exists.\n");
    return;
  }

  // Create an empty, unloaded resource
  ResourceManager::Resource new_resource;
  new_resource.resource_type = resource_type;
  new_resource.source_path = file_path;
  m_resources[resource_name] = new_resource;
}


void ResourceManager::start_async_load()
{
  printf("Begin async resource loading.\n");

  for (const auto& i: m_resources)
  {
    const Resource& r = i.second;
    // Set up the async load for each resource
    emscripten_async_wget_data(
      r.source_path.c_str(),
      (void*)&r,
      &f_onload,
      &f_onerr
    );
  }

  printf("End async resource loading.\n");
}


bool ResourceManager::getResource(const char* resource_name, unsigned int& resource_handle)
{
  resource_handle = m_resources[resource_name].handle;

  return false;
}
