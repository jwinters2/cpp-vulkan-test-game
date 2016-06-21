#include "Window.h"
#include "DetermineOS.h"

WINDOW::WINDOW(int width_a,int height_a,std::string name_a)
{
  width=width_a;
  height=height_a;
  name=name_a;
  isRunning=true;
  
  initWindow();
}

WINDOW::~WINDOW()
{
  deinitWindow();
}

bool WINDOW::getRunning()
{
  return isRunning;
}

void WINDOW::closeWindow()
{
  isRunning=false;  
}

void WINDOW::update()
{
  updateWindow();
}

//these aren't supposed to be here
#include <iostream>
void WINDOW::initWindow()
{
  std::cout<<name<<"\n";
}
void WINDOW::deinitWindow()
{
}
void WINDOW::updateWindow()
{
}
