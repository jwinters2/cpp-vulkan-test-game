#pragma once

#include <vector>

#include "WorldObject.h"
#include "GraphicsManager.h"

class WORLD_OBJECT;

class WORLD
{
  private:
    int frame;
    std::vector<WORLD_OBJECT *> objList;

  public:
    WORLD();
    int getFrame();
    bool isStillRunning();
    void worldLogic();
    void worldRender(GRAPHICS_MANAGER*);

    void addObject(WORLD_OBJECT*);
    void deleteObject(int);
};
