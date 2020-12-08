#include "ResourceManager.h"
#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif
#include <stdio.h>
#include "Texture.h"
#include "Mesh_obj.h"
#include "Mesh_pile.h"
#include "system_globals.h" // audio


void inspect(Mesh* mesh)
{
  printf("mesh ptr:0x%08x, vbo:%i, ", (Mesh*)mesh, (int)mesh->m_vbo_vertices);
  printf("ibo[%i]: ", mesh->m_matIboElements.size());
  for (int i = 0; i < mesh->m_matIboElements.size(); ++i)
  {
    printf("%i, ", mesh->m_matIboElements[i].elements);
  }
  printf("\n");
}


void ResourceManager::f_onload(void* arg, void* buffer, int size)
{
  Resource* r = (Resource*)arg;

  //printf("Resource %s has finished loading with %i bytes.\n", r->source_path.c_str(), size);

  if (r->resource_type == PNG)
  {
    //printf("processing texture.\n");
    Texture* t = new Texture();
    t->loadPng_fromMemory((const char*)buffer, size);
    r->handle = t->getID();
    r->loading_status = 100;
    // TODO t leaks
    //printf("done.\n");
  }
  else if (r->resource_type == OBJ)
  {
    //printf("processing mesh.\n");
    Mesh_obj* mesh = new Mesh_obj;
    mesh->load_obj_data((const char*)buffer, size);
    mesh->upload();
    r->handle = (unsigned int)((Mesh*)mesh);
    r->loading_status = 100;
    //printf("mesh ptr:0x%08x, vbo:%i, ", (Mesh*)mesh, mesh->m_vbo_vertices);
    //printf("ibo[%i]: ", mesh->m_matIboElements.size());
    // for (int i = 0; i < mesh->m_matIboElements.size(); ++i)
    // {
    //   printf("%i, ", mesh->m_matIboElements[i].elements);
    // }
    // printf("\n");

    // printf("done.\n");
  }
  else if (r->resource_type == PILE)
  {
    Mesh_pile* mesh = new Mesh_pile;
    mesh->load_obj_data((const char*)buffer, size);
    r->handle = (unsigned int)((Mesh*)mesh);
    r->loading_status = 100;
  }
  else if (r->resource_type == OGG)
  {
    g_audioManager.load_ogg_data((const char*)buffer, (unsigned int)size);
    g_audioManager.play(0, true);
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
    printf("A resource with that name already exists: %s\n", resource_name);
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
    //const Resource& r = i.second;
    const Resource* r = &m_resources[i.first];
    // Set up the async load for each resource
    emscripten_async_wget_data(
      r->source_path.c_str(),
      (void**)r,
      &f_onload,
      &f_onerr
    );
  }

  printf("End async resource loading.\n");
}


bool ResourceManager::getResource(const char* resource_name, unsigned int& resource_handle)
{
  //printf("getting \"%s\" (%i)\n", resource_name, m_resources[resource_name].loading_status);
  auto i = m_resources.find(resource_name);
  if (i == m_resources.end()) return false;

  resource_handle = i->second.handle;

  return true;
}


// bool ResourceManager::getResource(const char* resource_name, void*& resource_handle)
// {
//   resource_handle = (void*)m_resources[resource_name].handle;

//   return false;
// }


bool ResourceManager::getResource(const char* resource_name, void** resource_handle)
{
  //printf("getting \"%s\" (%i)\n", resource_name, m_resources[resource_name].loading_status);
  auto i = m_resources.find(resource_name);
  if (i == m_resources.end()) return false;

  if (i->second.loading_status == 100)
    *resource_handle = (void*)i->second.handle;

  return true;
}
