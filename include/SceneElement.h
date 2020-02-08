#pragma once


class RenderSystem;
class MeshBank;


class SceneElement
{
public:

  SceneElement() {}
  virtual ~SceneElement() {}

  //
  // Drawing
  //
  //virtual void draw() {}
  virtual void draw(RenderSystem* rs, MeshBank* mb) {}

  //
  // Input
  //
  virtual void cursor_pos_callback(double xpos, double ypos) {}
  virtual void mouse_button_callback(int button, int action, int mods) {}
  virtual void scroll_callback(double xoffset, double yoffset) {}

  virtual bool gamepad_callback(int eventType, const void* gamepadEvent, void *userData) { return false; }

  virtual void key_callback(int key, int scancode, int action, int mods) {}

  //
  // UI
  //
  virtual void UI() {}


  //
  // Update
  //
  virtual void update(double dt) {}


  //
  // Viewing
  //
  virtual void view(RenderSystem* rs) {}


protected:

  bool DRAW_ELEMENT = false;
  bool INPUT_ELEMENT = false;
  bool UI_ELEMENT = false;
  bool UPDATE_ELEMENT = false;
  bool VIEW_ELEMENT = false;

};
