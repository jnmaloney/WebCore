#include "MeshManager.h"
#include "Texture.h"


static MeshManager* s_singleton = 0;


MeshManager* MeshManager::get()
{
  return s_singleton;
}


MeshManager::MeshManager()
{
  s_singleton = this;
}


MeshManager::~MeshManager()
{

}


void MeshManager::load()
{
  std::vector<const char*> mesh_files;

  m_index[0] = mesh_files.size(); // Base
  mesh_files.push_back("data/obj/square.obj");
  mesh_files.push_back("data/obj/square.obj");
  mesh_files.push_back("data/obj/square.obj");
  mesh_files.push_back("data/obj/square.obj");
  mesh_files.push_back("data/obj/square.obj");
  mesh_files.push_back("data/obj/square.obj");
  mesh_files.push_back("data/obj/square.obj");
  mesh_files.push_back("data/obj/square.obj");
  mesh_files.push_back("data/obj/square.obj");
  mesh_files.push_back("data/obj/square.obj");
  mesh_files.push_back("data/obj/square.obj");
  mesh_files.push_back("data/obj/square.obj");
  mesh_files.push_back("data/obj/square.obj");
  mesh_files.push_back("data/obj/square.obj");
  mesh_files.push_back("data/obj/square.obj");
  mesh_files.push_back("data/obj/square.obj");
  mesh_files.push_back("data/obj/square.obj");
  mesh_files.push_back("data/obj/square.obj");
  mesh_files.push_back("data/obj/square.obj");
  mesh_files.push_back("data/obj/square.obj");
  mesh_files.push_back("data/obj/square.obj");
  mesh_files.push_back("data/obj/square.obj");
  mesh_files.push_back("data/obj/square.obj");
  mesh_files.push_back("data/obj/square.obj");
  mesh_files.push_back("data/obj/square.obj");
  mesh_files.push_back("data/obj/square.obj");
  mesh_files.push_back("data/obj/square.obj");
  mesh_files.push_back("data/obj/square.obj");
  mesh_files.push_back("data/obj/square.obj");
  mesh_files.push_back("data/obj/square.obj");
  mesh_files.push_back("data/obj/square.obj");
  mesh_files.push_back("data/obj/square.obj");
  mesh_files.push_back("data/obj/square.obj");
  mesh_files.push_back("data/obj/square.obj");
  mesh_files.push_back("data/obj/square.obj");
  mesh_files.push_back("data/obj/square.obj");
  mesh_files.push_back("data/obj/square.obj");
  mesh_files.push_back("data/obj/square.obj");
  mesh_files.push_back("data/obj/square.obj");
  mesh_files.push_back("data/obj/square.obj");
  mesh_files.push_back("data/obj/square.obj");
  mesh_files.push_back("data/obj/square.obj");
  mesh_files.push_back("data/obj/square.obj");
  mesh_files.push_back("data/obj/square.obj");
  mesh_files.push_back("data/obj/square.obj");
  mesh_files.push_back("data/obj/square.obj");
  mesh_files.push_back("data/obj/square.obj");
  mesh_files.push_back("data/obj/square.obj");
  mesh_files.push_back("data/obj/square.obj");
  mesh_files.push_back("data/obj/square.obj");
  mesh_files.push_back("data/obj/square.obj");
  mesh_files.push_back("data/obj/square.obj");
  mesh_files.push_back("data/obj/square.obj");
  mesh_files.push_back("data/obj/square.obj");
  mesh_files.push_back("data/obj/square.obj");
  mesh_files.push_back("data/obj/square.obj");
  for (int i = 0; i < 30; ++i) mesh_files.push_back("data/obj/square.obj");

  m_index[1] = mesh_files.size(); // 1 objects
  mesh_files.push_back("data/obj/square.obj");
  mesh_files.push_back("data/obj/square.obj");
  mesh_files.push_back("data/obj/square.obj");

  mesh_files.push_back("data/obj/square.obj");
  mesh_files.push_back("data/obj/square.obj");
  mesh_files.push_back("data/obj/square.obj");

  mesh_files.push_back("data/obj/square.obj");
  mesh_files.push_back("data/obj/square.obj");

  for (int i = 0; i < 10; ++i) mesh_files.push_back("data/obj/square.obj");

  m_index[2] = mesh_files.size(); // Do
  mesh_files.push_back("data/obj/square.obj");
  mesh_files.push_back("data/obj/square.obj");
  mesh_files.push_back("data/obj/square.obj");
  mesh_files.push_back("data/obj/square.obj");
  mesh_files.push_back("data/obj/square.obj");

  m_index[3] = mesh_files.size(); // Backgrounds
  mesh_files.push_back("data/obj/square.obj");
  mesh_files.push_back("data/obj/square.obj");
  mesh_files.push_back("data/obj/square.obj");
  mesh_files.push_back("data/obj/square.obj");
  mesh_files.push_back("data/obj/square.obj");
  mesh_files.push_back("data/obj/square.obj");

  m_index[4] = mesh_files.size(); // Other Characters
  mesh_files.push_back("data/obj/square.obj");
  mesh_files.push_back("data/obj/square.obj");
  mesh_files.push_back("data/obj/square.obj");
  mesh_files.push_back("data/obj/square.obj");
  mesh_files.push_back("data/obj/square.obj");
  mesh_files.push_back("data/obj/square.obj");
  mesh_files.push_back("data/obj/square.obj");
  mesh_files.push_back("data/obj/square.obj");
  mesh_files.push_back("data/obj/square.obj");
  mesh_files.push_back("data/obj/square.obj");
  mesh_files.push_back("data/obj/square.obj");
  mesh_files.push_back("data/obj/square.obj");
  mesh_files.push_back("data/obj/square.obj");



  std::vector<const char*> texture_files;
  texture_files.push_back("data/img/tiles/grass dirt.png");
  texture_files.push_back("data/img/tiles/grass top.png");
  texture_files.push_back("data/img/tiles/desert1.png");
  texture_files.push_back("data/img/tiles/desert2.png");
  texture_files.push_back("data/img/tiles/desert3.png");
  texture_files.push_back("data/img/tiles/desert4.png");
  texture_files.push_back("data/img/tiles/desert5.png");
  texture_files.push_back("data/img/tiles/desert6.png");
  texture_files.push_back("data/img/tiles/cave_tileset1.png");
  texture_files.push_back("data/img/tiles/cave_tileset2.png");
  texture_files.push_back("data/img/tiles/cave_tileset3.png");
  texture_files.push_back("data/img/tiles/cave_tileset4.png");
  texture_files.push_back("data/img/tiles/cave_tileset5.png");
  texture_files.push_back("data/img/tiles/cave_tileset6.png");
  texture_files.push_back("data/img/tiles/cave_tileset7.png");
  texture_files.push_back("data/img/tiles/cave_tileset8.png");
  texture_files.push_back("data/img/tiles/cave_tileset9.png");
  texture_files.push_back("data/img/tiles/cave_tileset10.png");
  texture_files.push_back("data/img/tiles/cave_tileset11.png");
  texture_files.push_back("data/img/tiles/cave_tileset12.png");
  texture_files.push_back("data/img/tiles/cave_r6.png");
  texture_files.push_back("data/img/tiles/cave_r5.png");
  texture_files.push_back("data/img/tiles/cave_r4.png");
  texture_files.push_back("data/img/tiles/cave_r3.png");
  texture_files.push_back("data/img/tiles/cave_r2.png");
  texture_files.push_back("data/img/tiles/cave_r1.png");
  texture_files.push_back("data/img/tiles/cave_l6.png");
  texture_files.push_back("data/img/tiles/cave_l5.png");
  texture_files.push_back("data/img/tiles/cave_l4.png");
  texture_files.push_back("data/img/tiles/cave_l3.png");
  texture_files.push_back("data/img/tiles/cave_l2.png");
  texture_files.push_back("data/img/tiles/cave_l1.png");
  texture_files.push_back("data/img/tiles/dungeon floor.png");
  texture_files.push_back("data/img/tiles/dungeon f1.png");
  texture_files.push_back("data/img/tiles/dungeon f2.png");
  texture_files.push_back("data/img/tiles/dungeon f3.png");
  texture_files.push_back("data/img/tiles/dungeon b1.png");
  texture_files.push_back("data/img/tiles/dungeon b2.png");
  texture_files.push_back("data/img/tiles/dungeon b3.png");
  texture_files.push_back("data/img/tiles/dungeon b4.png");
  texture_files.push_back("data/img/tiles/dungeon b5.png");
  texture_files.push_back("data/img/tiles/dungeon b6.png");
  texture_files.push_back("data/img/tiles/dungeon b7.png");
  texture_files.push_back("data/img/tiles/dungeon b8.png");
  texture_files.push_back("data/img/tiles/dungeon b9.png");
  texture_files.push_back("data/img/tiles/dungeon barrel.png");
  texture_files.push_back("data/img/tiles/Temple floor 1.png");
  texture_files.push_back("data/img/tiles/Temple floor 2.png");
  texture_files.push_back("data/img/tiles/Temple floor 3.png");
  texture_files.push_back("data/img/tiles/Temple floor 4.png");
  texture_files.push_back("data/img/tiles/Temple floor 5.png");
  texture_files.push_back("data/img/tiles/Temple floor 6.png");
  texture_files.push_back("data/img/tiles/Temple floor l1.png");
  texture_files.push_back("data/img/tiles/Temple floor r1.png");
  texture_files.push_back("data/img/tiles/Temple brick 1.png");
  texture_files.push_back("data/img/tiles/Temple brick 2.png");

  texture_files.push_back("data/img/tiles/brickWhiteB.png");
  texture_files.push_back("data/img/tiles/brickWhiteBL.png");
  texture_files.push_back("data/img/tiles/brickWhiteBR.png");
  texture_files.push_back("data/img/tiles/brickWhiteL.png");
  texture_files.push_back("data/img/tiles/brickWhiteR.png");
  texture_files.push_back("data/img/tiles/brickWhiteT.png");  // 62
  texture_files.push_back("data/img/tiles/brickWhiteTL.png"); // 63
  texture_files.push_back("data/img/tiles/brickWhiteTR.png"); // 64
  texture_files.push_back("data/img/tiles/brickYellowBL.png");
  texture_files.push_back("data/img/tiles/brickYellowBR.png");
  texture_files.push_back("data/img/tiles/brickYellowTL.png"); // 67
  texture_files.push_back("data/img/tiles/brickYellowTR.png"); // 68

  texture_files.push_back("data/img/tiles/dungeon_000.png");
  texture_files.push_back("data/img/tiles/dungeon_002.png");
  texture_files.push_back("data/img/tiles/dungeon_009.png");
  texture_files.push_back("data/img/tiles/dungeon_010.png");
  texture_files.push_back("data/img/tiles/dungeon_011.png");
  texture_files.push_back("data/img/tiles/dungeon_012.png");
  texture_files.push_back("data/img/tiles/dungeon_013.png");
  texture_files.push_back("data/img/tiles/dungeon_018.png");
  texture_files.push_back("data/img/tiles/dungeon_022.png");
  texture_files.push_back("data/img/tiles/dungeon_023.png");
  texture_files.push_back("data/img/tiles/dungeon_024.png");
  texture_files.push_back("data/img/tiles/dungeon_025.png");
  texture_files.push_back("data/img/tiles/dungeon_026.png");
  texture_files.push_back("data/img/tiles/dungeon_044.png");
  texture_files.push_back("data/img/tiles/dungeon_045.png");
  texture_files.push_back("data/img/tiles/dungeon_108.png");
  texture_files.push_back("data/img/tiles/dungeon_109.png");
  texture_files.push_back("data/img/tiles/dungeon_110.png");



  texture_files.push_back("data/img/portal.png");
  texture_files.push_back("data/img/cloud.png");
  texture_files.push_back("data/img/bush.png");

  texture_files.push_back("data/img/cave_tileset_door.png");
  texture_files.push_back("data/img/cave_tileset_cave.png");
  texture_files.push_back("data/img/cave_tileset_cave_top.png");

  texture_files.push_back("data/img/char/Prison_closed.png");
  texture_files.push_back("data/img/char/Prison_open.png");

  texture_files.push_back("data/img/gem1.png");
  texture_files.push_back("data/img/gem2.png");
  texture_files.push_back("data/img/gem3.png");
  texture_files.push_back("data/img/gem4.png");
  texture_files.push_back("data/img/portal0.png");
  texture_files.push_back("data/img/portal_l1.png");
  texture_files.push_back("data/img/portal_l2.png");
  texture_files.push_back("data/img/portal_l3.png");
  texture_files.push_back("data/img/portal_l4.png");
  texture_files.push_back("data/img/portal_l5.png");



  texture_files.push_back("data/img/do1.png");
  texture_files.push_back("data/img/do2.png");
  texture_files.push_back("data/img/dou.png");
  texture_files.push_back("data/img/dod.png");
  texture_files.push_back("data/img/docry.png");

  texture_files.push_back("data/img/bkg/background1.png");
  texture_files.push_back("data/img/bkg/background2.png");
  texture_files.push_back("data/img/bkg/background3.png");
  texture_files.push_back("data/img/bkg/background4.png");
  texture_files.push_back("data/img/bkg/background5.png");
  texture_files.push_back("data/img/bkg/SunsetTempleBackground1.png");


  texture_files.push_back("data/img/char/Minions 1a.png");
  texture_files.push_back("data/img/char/Re.png");
  texture_files.push_back("data/img/char/Mi.png");
  texture_files.push_back("data/img/char/Fa.png");
  texture_files.push_back("data/img/char/So.png");
  texture_files.push_back("data/img/char/La.png");
  texture_files.push_back("data/img/char/Si.png");
  texture_files.push_back("data/img/char/Cd.png");
  texture_files.push_back("data/img/char/Headset.png");
  texture_files.push_back("data/img/char/Mic.png");
  texture_files.push_back("data/img/char/Speaker.png");
  texture_files.push_back("data/img/char/Piano.png");
  texture_files.push_back("data/img/char/Dark Do.png");




  for ( int i = 0; i < mesh_files.size(); ++i )
  {
    Mesh* mesh = new Mesh();

    mesh->load_obj(mesh_files[i]);
    mesh->upload_obj();

    if (texture_files[i])
    {
      mesh->texture = new Texture();
      mesh->texture->loadPng(texture_files[i]);
    }

    m_meshes.push_back(mesh);
  }

}


int MeshManager::getMeshIndex(int t, int index)
{
  int i0 = m_index[t];
  return index + i0;
}


Mesh* MeshManager::getMesh(int index)
{
  if (index >= m_meshes.size()) return m_meshes[0];

  return m_meshes[index];
}
