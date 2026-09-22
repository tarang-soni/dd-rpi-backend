//
// Created by sonit on 22-09-2026.
//

#ifndef RPI_BACKEND_DISCOVERYSERVER_H
#define RPI_BACKEND_DISCOVERYSERVER_H
#include <atomic>
#include <functional>

#include "T_UDPSocket.h"

namespace dd_rpi_backend
{
    class DiscoveryServer
    {
    public:
        using DiscoveryHandler = std::function<void(const std::string& ip,uint16_t port)>;
        void bind(const uint16_t port);
        void stop();
        void listenLoop();
        inline void setConnectCallback(const DiscoveryHandler &handler){m_handler = handler; }
    private:
        void processDiscoveryRequest();
        void sendReply();

        std::atomic<bool> m_listening{false};
        std::unique_ptr<T_UDPSocket> m_udp = nullptr;
        DiscoveryHandler m_handler;

    };
} // dd_rpi_backend

#endif //RPI_BACKEND_DISCOVERYSERVER_H