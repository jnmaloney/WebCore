#pragma once


#include "Scene.h"
#include "RenderSystem.h"
#include "MeshBank.h"
#include <map>
#include <string>


class SceneManager
{
public:

  SceneManager();
  ~SceneManager();

  void init();

  void addScene(std::string id, Scene* scene);

  void loadSceneFile(std::string filename);

  void draw(RenderSystem& rs);

  void setScene(std::string id);

  void cursor_pos_callback(double xpos, double ypos);
  void mouse_button_callback(int button, int action, int mods);
  void scroll_callback(double xoffset, double yoffset);

  void update(double dt);

  void view(RenderSystem& rs);


protected:

  std::map<std::string, Scene*> m_scenes;
  Scene* m_currentScene = 0;

  MeshBank m_meshBank;
};
