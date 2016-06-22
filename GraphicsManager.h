#pragma once

#include "DetermineOS.h"
#include "Window.h"

class GRAPHICS_MANAGER
{
  public:
    GRAPHICS_MANAGER();
    ~GRAPHICS_MANAGER();
    void drawText(int);
    void drawText(char const*);
    void drawTextnl(int);
    void drawTextnl(char const*);

    void preRender();
    void postRender();

  private:
    VkInstance      vulkan_instance;
    VkDevice        vulkan_device;
    VkCommandPool   vulkan_command_pool;
    VkCommandBuffer vulkan_command_buffer;
    VkCommandBufferBeginInfo vulkan_command_buffer_begin_info {};

    WINDOW * game_window=NULL;
    
    void init();
    void deinit();
    void initDevice();
    void deinitDevice();
    void initCommandPool();
    void deinitCommandPool();
    void initCommandBuffer();
    void deinitCommandBuffer();
};
