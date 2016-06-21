#pragma once

#include "DetermineOS.h"
#include <string>

class WINDOW
{
  public:
    //declared in general file
    WINDOW(int,int,std::string);
    ~WINDOW();
    bool getRunning();
    void update();

  private:
    //declared in OS-specific file
    void initWindow();
    void deinitWindow();
    void updateWindow();

    //declared in general file
    void closeWindow();
    
    int width;
    int height;
    std::string name;
    bool isRunning;
};
