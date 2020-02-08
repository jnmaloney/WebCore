#include "Scene.h"
#include "SceneElement.h"


Scene::Scene()
{

}


Scene::~Scene()
{

}


void Scene::addSceneElement(SceneElement* element)
{
  m_elements.push_back(element);
}


void Scene::drawScene(RenderSystem* rs, MeshBank* mb)
{
  for (auto& i : m_elements)
  {
    //if (i->DRAW_ELEMENT)
    i->draw(rs, mb);
  }
}


void Scene::cursor_pos_callback(double xpos, double ypos)
{
  for (auto& i : m_elements)
  {
    i->cursor_pos_callback(xpos, ypos);
  }
}


void Scene::mouse_button_callback(int button, int action, int mods)
{
  for (auto& i : m_elements)
  {
    i->mouse_button_callback(button, action, mods);
  }
}


void Scene::scroll_callback(double xoffset, double yoffset)
{
  for (auto& i : m_elements)
  {
    i->scroll_callback(xoffset, yoffset);
  }
}


void Scene::update(double dt)
{
  for (auto& i : m_elements)
  {
    i->update(dt);
  }
}


void Scene::view(RenderSystem* rs)
{
  for (auto& i : m_elements)
  {
    i->view(rs);
  }
}
