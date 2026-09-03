//
// Created by sonit on 29-07-2026.
//

#ifndef RPI_BACKEND_WINCLIENTSOCKET_H
#define RPI_BACKEND_WINCLIENTSOCKET_H
#include "../../TClientSocket.h"
#include <winsock2.h>
#include <ws2tcpip.h>

#include "Protocols.h"
#pragma comment(lib, "ws2_32.lib")
namespace dd_rpi_backend
{
    class WinClientSocket:public TClientSocket
    {
        public:
        WinClientSocket();
        ~WinClientSocket() override;
        bool connect(const char* ip_addr,uint16_t port) override;

        bool send(const ClientResponse& message) override;
        ServerCommand receive() override;
        void close() override;
    private:
        SOCKET s;
    };
} // dd_rpi_backend

#endif //RPI_BACKEND_WINCLIENTSOCKET_H