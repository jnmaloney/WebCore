#pragma once


#include <list>
#include <string>


class SceneElement;
class RenderSystem;
class MeshBank;


class Scene
{
public:

  Scene();
  ~Scene();

  void addSceneElement(SceneElement* element);

  void drawScene(RenderSystem* rs, MeshBank* mb);
  void drawUI();

  void loadSceneFile();

  void cursor_pos_callback(double xpos, double ypos);
  void mouse_button_callback(int button, int action, int mods);
  void scroll_callback(double xoffset, double yoffset);

  void update(double dt);

  void view(RenderSystem* rs);

protected:

  std::list<SceneElement*> m_elements;
};
