#include <iostream>

#include "WorldObject.h"
#include "World.h"

int WORLD_OBJECT::idGenerator=0;

WORLD_OBJECT::WORLD_OBJECT()
{
  age=0;
  assignId();
}

void WORLD_OBJECT::logic(WORLD* w)
{
  /*
  if(w->getFrame()==(id+2)*(id+2))
  {
    w->deleteObject(id);
  }
  */
  if(age!=0)
  {
    w->addObject(new WORLD_OBJECT());
  }

  age++;
  if(age==2)
  {
    w->deleteObject(id);
  }
}

void WORLD_OBJECT::render(GRAPHICS_MANAGER* gr)
{
  gr->drawText(id);
  gr->drawText(" ");
}

int WORLD_OBJECT::getId()
{
  return id;
}

void WORLD_OBJECT::assignId()
{
  id=idGenerator++;
}
