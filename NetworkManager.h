//
// Created by sonit on 05-08-2026.
//

#ifndef RPI_BACKEND_NETWORKMANAGER_H
#define RPI_BACKEND_NETWORKMANAGER_H
#include <thread>

#include "CommandListener.h"
#include "DiscoveryServer.h"

namespace dd_rpi_backend
{
    class NetworkManager
    {
    public:
        using CommandHandler = std::function<void(ServerCommand)>;
        NetworkManager();
        ~NetworkManager();

        //void start(const std::string& host,uint16_t port,CommandHandler handler);//delete later after implementation
        void stop();
        void sendResponse(ClientResponse response);

        void startDiscovery(uint16_t port);
        void stopDiscovery(uint16_t port);
        void tcpConnect(const std::string& host,uint16_t port);
    private:

        CommandListener m_commandListener;
        DiscoveryServer m_discoveryServer;
        std::thread m_commandThread;
        std::thread m_discoveryThread;

    };
}
#endif //RPI_BACKEND_NETWORKMANAGER_H