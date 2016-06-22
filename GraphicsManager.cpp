#include "GraphicsManager.h"

#include <iostream>
#include <vector>
#include "DetermineOS.h"

GRAPHICS_MANAGER::GRAPHICS_MANAGER()
{
  init();
  initDevice();
  initCommandPool();
  initCommandBuffer();

  game_window = new WINDOW(&vulkan_instance,800,600,"test game");
}

GRAPHICS_MANAGER::~GRAPHICS_MANAGER()
{
  drawText("\n");
  deinitCommandBuffer();
  deinitCommandPool();
  deinitDevice();
  deinit();
}

void GRAPHICS_MANAGER::drawText(int a)
{
  std::cout<<a;
}

void GRAPHICS_MANAGER::drawText(char const* a)
{
  std::cout<<a;
}

void GRAPHICS_MANAGER::drawTextnl(int a)
{
  std::cout<<a<<"\n";
}

void GRAPHICS_MANAGER::drawTextnl(char const* a)
{
  std::cout<<a<<"\n";
}

void GRAPHICS_MANAGER::init()
{
  //initalizes application info needed for instance info
  VkApplicationInfo vulkan_application_info;
  vulkan_application_info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
  vulkan_application_info.pApplicationName = "Testing Vulkan and Practicing Coding";
  vulkan_application_info.apiVersion = VK_MAKE_VERSION(1,0,16);

  //initalizes instance info needed for making an instance
  VkInstanceCreateInfo vulkan_create_info {};
  vulkan_create_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
  vulkan_create_info.pApplicationInfo = &vulkan_application_info;

  //makes an instance
  auto error = vkCreateInstance(&vulkan_create_info,NULL,&vulkan_instance);
  if(error!=0)
  {
    drawTextnl("Init failed");
  }
  else
  {
    drawTextnl("Init succeeded");
  }
}

void GRAPHICS_MANAGER::deinit()
{
  drawTextnl("deinit");
  vkDestroyInstance(vulkan_instance,NULL);
}

void GRAPHICS_MANAGER::initDevice()
{
  //stores the number of plysical devices (GPU's)
  uint32_t vulkan_physical_device_count;

  //puts the number of devices into vulkan_physical_device_count, since the last parameter is NULL
  vkEnumeratePhysicalDevices(vulkan_instance,&vulkan_physical_device_count,NULL);
  drawTextnl(vulkan_physical_device_count);

  //makes a vector to store the devices
  std::vector<VkPhysicalDevice> vulkan_physical_device_list(vulkan_physical_device_count);
  //puts the devices found into vulkan_physical_device_list
  vkEnumeratePhysicalDevices(vulkan_instance,&vulkan_physical_device_count,vulkan_physical_device_list.data());

  //stores the first device on its own
  VkPhysicalDevice vulkan_physical_device = vulkan_physical_device_list.at(0);

  //initalizes VkDeviceQueueCreateInfo needed for making a VkDeviceCreateInfo
  VkDeviceQueueCreateInfo vulkan_queue_creation_info {};
  vulkan_queue_creation_info.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;

  //initalizes VkDeviceCreateInfo needed for making a device
  VkDeviceCreateInfo vulkan_device_creation_info {};
  vulkan_device_creation_info.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
  vulkan_device_creation_info.pQueueCreateInfos = &vulkan_queue_creation_info;

  auto error=vkCreateDevice(vulkan_physical_device,&vulkan_device_creation_info,NULL,&vulkan_device);
  //int error=1;
  if(error!=0)
  {
    drawTextnl("Device init failed");
  }
  else
  {
    drawTextnl("Device init succeeded");
  }
}

void GRAPHICS_MANAGER::deinitDevice()
{
  drawTextnl("deinit device");
  vkDestroyDevice(vulkan_device,NULL);
}

void GRAPHICS_MANAGER::initCommandPool()
{
  //created command pool info required for making command pool
  VkCommandPoolCreateInfo vulkan_command_pool_info {};
  vulkan_command_pool_info.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
  //creates the command pool
  auto error=vkCreateCommandPool(vulkan_device,&vulkan_command_pool_info,NULL,&vulkan_command_pool);
  if(error!=0)
  {
    drawTextnl("Command Pool init failed");
  }
  else
  {
    drawTextnl("Command Pool init succeeded");
  }
}

void GRAPHICS_MANAGER::deinitCommandPool()
{
  drawTextnl("deinit command pool");
  vkDestroyCommandPool(vulkan_device,vulkan_command_pool,NULL);
}

void GRAPHICS_MANAGER::initCommandBuffer()
{
  //created command buffer info required for making command buffer
  VkCommandBufferAllocateInfo vulkan_cbuffer_allocate_info {};
  vulkan_cbuffer_allocate_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
  vulkan_cbuffer_allocate_info.commandPool = vulkan_command_pool;
  vulkan_cbuffer_allocate_info.commandBufferCount = 1;
  vulkan_cbuffer_allocate_info.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;

  //creates command buffer
  auto error=vkAllocateCommandBuffers(vulkan_device,&vulkan_cbuffer_allocate_info,&vulkan_command_buffer);
  if(error!=0)
  {
    drawTextnl("Command Buffer init failed");
  }
  else
  {
    drawTextnl("Command Buffer init succeeded");
  }

  //needed to begin the command buffer to accept commands
  //doing this in the actual function is redundant
  vulkan_command_buffer_begin_info.sType=VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
}

void GRAPHICS_MANAGER::deinitCommandBuffer()
{
  drawTextnl("deinit command buffer");
  VkCommandBuffer vulkan_command_buffer_array = vulkan_command_buffer;
  vkFreeCommandBuffers(vulkan_device,vulkan_command_pool,1,&vulkan_command_buffer_array);
}

void GRAPHICS_MANAGER::preRender()
{
  auto error=vkBeginCommandBuffer(vulkan_command_buffer,&vulkan_command_buffer_begin_info);
  if(error!=0)
  {
    drawText("PreRender failed <");
  }
}

void GRAPHICS_MANAGER::postRender()
{
  auto error=vkEndCommandBuffer(vulkan_command_buffer);
  if(error!=0)
  {
    drawText("> PostRender failed");
  }

  game_window->update();
}
