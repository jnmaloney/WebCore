#include "graphics.h"

#include "InputSystem.h"
#include "RenderSystem.h"
#include "WindowManager.h"
#include "MenuManager.h"
#include "AudioManager.h"

#include "Random.h"




class OdinEngine
{
public:

  OdinEngine()
  {
    Random::init();
  }

  WindowManager windowManager;
  RenderSystem rs;
  MenuManager menuManager;
};
