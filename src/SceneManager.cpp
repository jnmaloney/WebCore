#include "SceneManager.h"
#include "RenderSystem.h"


SceneManager::SceneManager()
{

}

void SceneManager::init()
{
<<<<<<< HEAD
  //m_meshBank.add("square", "data/obj/square.obj", "data/img/tile.png");
  //m_meshBank.load();
=======
  m_meshBank.add("square", "data/obj/square.obj", "data/img/tile.png");
  m_meshBank.load();
>>>>>>> 51cef8f22afefb184093a34d45f0818a38d0d2d5
}


SceneManager::~SceneManager()
{

}


void SceneManager::addScene(std::string id, Scene* scene)
{
  m_scenes[id] = scene;
  m_currentScene = scene;
}


void SceneManager::draw(RenderSystem& rs)
{
  m_currentScene->drawScene(&rs, &m_meshBank);
}


void SceneManager::cursor_pos_callback(double xpos, double ypos)
{
  m_currentScene->cursor_pos_callback(xpos, ypos);
}


void SceneManager::mouse_button_callback(int button, int action, int mods)
{
  m_currentScene->mouse_button_callback(button, action, mods);
}


void SceneManager::scroll_callback(double xoffset, double yoffset)
{
  m_currentScene->scroll_callback(xoffset, yoffset);
}


<<<<<<< HEAD
void SceneManager::key_callback(int key, int scancode, int action, int mods)
{
  m_currentScene->key_callback(key, scancode, action, mods);
}


=======
>>>>>>> 51cef8f22afefb184093a34d45f0818a38d0d2d5
void SceneManager::update(double dt)
{
  m_currentScene->update(dt);
}


void SceneManager::view(RenderSystem& rs)
{
<<<<<<< HEAD
  m_currentScene->view(&rs);
=======
  m_currentScene->view(&rs);  
>>>>>>> 51cef8f22afefb184093a34d45f0818a38d0d2d5
}
