#pragma once

#if defined(_WIN32)
  #define VK_USE_PLATFORM_WIN32_KHR 1
  #include <windows.h>
#elif defined(__linux)
  #define VK_USE_PLATFORM_XCB_KHR 1
  #include <xcb/xcb.h>
#else
  #error I have not added support for that platform yet
#endif

#include <vulkan/vulkan.h>
