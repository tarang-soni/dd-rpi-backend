#include <iostream>
#include "Application.h"

int main()
{
    //init winsock
    dd_rpi_backend::Application app;
    if (!app.init())
    {
        std::cerr << "Failed to initialize" << std::endl;
        return -1;
    }
    app.run();
    return 0;
}
