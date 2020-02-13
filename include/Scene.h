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
<<<<<<< HEAD
  void key_callback(int key, int scancode, int action, int mods);
=======
>>>>>>> 51cef8f22afefb184093a34d45f0818a38d0d2d5

  void update(double dt);

  void view(RenderSystem* rs);

protected:

  std::list<SceneElement*> m_elements;
};
