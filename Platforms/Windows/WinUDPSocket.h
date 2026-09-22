//
// Created by sonit on 22-09-2026.
//

#ifndef RPI_BACKEND_WINUDPSOCKET_H
#define RPI_BACKEND_WINUDPSOCKET_H
#include "T_UDPSocket.h"
#include <winsock2.h>
#include <ws2tcpip.h>

namespace dd_rpi_backend
{
    class WinUDPSocket:public T_UDPSocket
    {
        public:
        WinUDPSocket();
        ~WinUDPSocket() override;
        virtual bool bind(uint16_t port) override;
        virtual int sendTo(const std::string& data,const std::string& ip,uint16_t port) override;
        virtual bool receiveFrom(std::string& data,std::string& senderIp,uint16_t& senderPort) override;
        virtual void close() override;

    private:
        SOCKET s;
    };
} // dd_rpi_backend

#endif //RPI_BACKEND_WINUDPSOCKET_H