#include <iostream>
#include "Application.h"
#if defined(_WIN32) || defined(_WIN64)
#include <winsock2.h>
#endif
int main()
{
    //init winsock
#if defined(_WIN32) || defined(_WIN64)
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2,2),&wsaData)!=0)
    {
        std::cerr << "UDP WSAStartup failed." << std::endl;
        return -1;
    }
#endif

    dd_rpi_backend::Application app;
    if (!app.init())
    {
        std::cerr << "Failed to initialize" << std::endl;
        return -1;
    }
    app.run();
#if defined(_WIN32) || defined(_WIN64)
    WSACleanup();
#endif

    return 0;
}
