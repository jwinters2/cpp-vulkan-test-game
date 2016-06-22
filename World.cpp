#include <iostream>
#include <vector>
#include <algorithm>

#include "WorldObject.h"
#include "World.h"

WORLD::WORLD()
{
  frame=0;
}

bool WORLD::isStillRunning()
{
  if(frame>100)
  {
    return false;
  }
  return true;
}

int WORLD::getFrame()
{
  return frame;
}

void WORLD::worldLogic()
{
  frame++;
  //std::cout<<"\n"<<frame<<": ";

  for(int i=0;i<objList.size();i++)
  {
    objList.at(i)->logic(this);
  }
}

void WORLD::worldRender(GRAPHICS_MANAGER* gr)
{
  gr->preRender();

  gr->drawText("\n");
  gr->drawText(frame);
  gr->drawText(": ");

  for(int i=0;i<objList.size();i++)
  {
    objList.at(i)->render(gr);
  }

  gr->postRender();
}

void WORLD::addObject(WORLD_OBJECT* obj)
{
  objList.push_back(obj);
}

void WORLD::deleteObject(int id)
{
  for(int i=0;i<objList.size();i++)
  {
    if(objList.at(i)->getId()==id)
    {
      //delete objList.at(i);
      objList.erase(objList.begin()+i);
      break;
    }
  }
}
