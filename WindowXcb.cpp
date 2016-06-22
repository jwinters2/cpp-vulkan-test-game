//creates window using XCB, which I think is linux's X-server
//credit to Niko Kauppi for the base code

#include "DetermineOS.h"
#include "Window.h"

#include <iostream>

#if VK_USE_PLATFORM_XCB_KHR
  void  WINDOW::initWindow()
  {
    //connect to X11 server
    const xcb_setup_t * setup=NULL;
    xcb_screen_iterator_t it;
    int screen=0;
    
    window_xcb_connection = xcb_connect(NULL,&screen);
    if(window_xcb_connection == NULL)
    {
      std::cout<<"XCB connection failed\n";
      exit(-1);
    }

    setup = xcb_get_setup(window_xcb_connection);
    it = xcb_setup_roots_iterator(setup);
    while(screen-- > 0)
    {
      xcb_screen_next(&it);
    }
    window_xcb_screen = it.data;

    //create the window
    VkRect2D dim = {{0,0},{width,height}};

    uint32_t value_mask,value_list[32];

    window_xcb_window = xcb_generate_id(window_xcb_connection);

    value_mask = XCB_CW_BACK_PIXEL | XCB_CW_EVENT_MASK; 
    value_list[0] = window_xcb_screen->black_pixel;
    value_list[1] = XCB_EVENT_MASK_KEY_RELEASE | XCB_EVENT_MASK_EXPOSURE;

    xcb_create_window(window_xcb_connection,
                      XCB_COPY_FROM_PARENT,
                      window_xcb_window,
                      window_xcb_screen->root,
                      dim.offset.x,
                      dim.offset.y,
                      dim.extent.width,
                      dim.extent.height,
                      0,
                      XCB_WINDOW_CLASS_INPUT_OUTPUT,
                      window_xcb_screen->root_visual,
                      value_mask,
                      value_list);

    //sends destroy signal to window when we want to
    xcb_intern_atom_cookie_t cookie = xcb_intern_atom(window_xcb_connection,1,12,"WM_PROTOCALS");
    xcb_intern_atom_reply_t * reply = xcb_intern_atom_reply(window_xcb_connection,cookie,0);

    xcb_intern_atom_cookie_t cookie2 = xcb_intern_atom(window_xcb_connection,0,16,"WM_DELETE_WINDOW");
    window_xcb_atom_window_reply = xcb_intern_atom_reply(window_xcb_connection,cookie2,0);

    xcb_change_property(window_xcb_connection,
                        XCB_PROP_MODE_REPLACE,
                        window_xcb_window,
                        (*reply).atom,
                        4,
                        32,
                        1,
                        &(*window_xcb_atom_window_reply).atom);
    free(reply);

    xcb_map_window(window_xcb_connection,window_xcb_window);

    //force screen resolution
    const uint32_t coords[] = {width,height};
    xcb_configure_window(window_xcb_connection,
                         window_xcb_window,
                         XCB_CONFIG_WINDOW_X | XCB_CONFIG_WINDOW_Y,
                         coords);
    xcb_flush(window_xcb_connection);

    std::cout<<"Window Init Succeeded\n";

    //creates gives the surface to vulkan to handle
    VkXcbSurfaceCreateInfoKHR vulkan_surface_create_info {};
    vulkan_surface_create_info.sType = VK_STRUCTURE_TYPE_XCB_SURFACE_CREATE_INFO_KHR;
    vulkan_surface_create_info.connection = window_xcb_connection;
    vulkan_surface_create_info.window = window_xcb_window;
    auto error=vkCreateXcbSurfaceKHR((*vulkan_instance_pointer),&vulkan_surface_create_info,NULL,&vulkan_surface);
    if(error!=0)
    {
      std::cout<<"surface init failed\n";
    }
    else
    {
      std::cout<<"surface init succeeded\n";
    }
  }

  void WINDOW::deinitWindow()
  {
    xcb_destroy_window(window_xcb_connection,window_xcb_window);
    xcb_disconnect(window_xcb_connection);
    window_xcb_window = 0;
    window_xcb_connection = NULL;
  }

  void WINDOW::updateWindow()
  {
    xcb_generic_event_t * event = xcb_poll_for_event(window_xcb_connection);
    if(!event)
    {
      return;
    }

    switch(event->response_type & ~0x80)
    {
      case XCB_CLIENT_MESSAGE:
        if(((xcb_client_message_event_t*)event)->data.data32[0] == window_xcb_atom_window_reply->atom)
        {
          closeWindow();          
        }
        break;
      default:
        break;
    }
    free(event);
  }
#endif
