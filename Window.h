#pragma once

#include "DetermineOS.h"
#include <string>

class WINDOW
{
  public:
    //declared in general file
    WINDOW(VkInstance*,uint32_t,uint32_t,std::string);
    ~WINDOW();
    bool getRunning();
    void update();

    //OS-specific functions
    #if VK_USE_PLATFORM_XCB_KHR
      xcb_connection_t        * getConnection();
      xcb_window_t              getWindow();
    #endif

  private:
    //declared in OS-specific file
    void initWindow();
    void deinitWindow();
    void updateWindow();

    //declared in general file
    void closeWindow();
    
    //general variables
    uint32_t width;
    uint32_t height;
    std::string name;
    bool isRunning;
    VkSurfaceKHR vulkan_surface;
    VkInstance* vulkan_instance_pointer;
    
    //OS-specific files 
    #if VK_USE_PLATFORM_XCB_KHR
      xcb_connection_t        * window_xcb_connection = NULL;
      xcb_screen_t            * window_xcb_screen = NULL;
      xcb_window_t              window_xcb_window = 0;
      xcb_intern_atom_reply_t * window_xcb_atom_window_reply = NULL;
    #endif
};
