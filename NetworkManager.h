//
// Created by sonit on 05-08-2026.
//

#ifndef RPI_BACKEND_NETWORKMANAGER_H
#define RPI_BACKEND_NETWORKMANAGER_H
#include <thread>

#include "CommandListener.h"
namespace dd_rpi_backend
{
    class NetworkManager
    {
    public:
        using CommandHandler = std::function<void(ServerCommand)>;
        NetworkManager();
        ~NetworkManager();

        void start(const std::string& host,uint16_t port,CommandHandler handler);
        void stop();
        void sendResponse(ClientResponse response);
    private:

        CommandListener m_commandListener;
        std::thread m_listenerThread;

    };
}
#endif //RPI_BACKEND_NETWORKMANAGER_H