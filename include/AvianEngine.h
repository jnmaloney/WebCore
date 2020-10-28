#pragma once


class AvianEngine
{
public:
  AvianEngine();
  ~AvianEngine();

  void init();
  void quit();

  struct Settings
  {
    int screen_size_x = 800;
    int screen_size_y = 600;    
  };
  Settings settings;

  void beginLoop();
  void endLoop();
};