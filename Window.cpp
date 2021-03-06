#include "Window.h"
#include "DetermineOS.h"

WINDOW::WINDOW(VkInstance* vulkan_instance_a, uint32_t width_a,uint32_t height_a,std::string name_a)
{
  width=width_a;
  height=height_a;
  name=name_a;
  isRunning=true;
  vulkan_instance_pointer = vulkan_instance_a;
  
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
