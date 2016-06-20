#pragma once

#include "World.h"
#include "GraphicsManager.h"

class WORLD;

class WORLD_OBJECT
{
  private:
    int id;
    int age;
    static int idGenerator;

    void assignId();

  public:
    WORLD_OBJECT();
    void logic(WORLD*);
    void render(GRAPHICS_MANAGER*);
    int getId();
};
