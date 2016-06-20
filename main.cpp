#include <iostream>
#include "World.h"
#include "WorldObject.h"
#include "GraphicsManager.h"

int main()
{
  GRAPHICS_MANAGER gr;
  WORLD w;

  for(int i=0;i<10;i++)
  {
    w.addObject(new WORLD_OBJECT());
  }

  while(w.isStillRunning())
  {
    w.worldLogic();
    w.worldRender(&gr);
  }
}
