//
// Created by sonit on 29-07-2026.
//

#include "WinTcpSocket.h"

#include <iostream>
#include <ostream>

namespace dd_rpi_backend
{
    WinTcpSocket::WinTcpSocket()
    {
        s = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
        int flag = 1;
        // socketFd is your native socket handle
        setsockopt(s, IPPROTO_TCP, TCP_NODELAY, (char*)&flag, sizeof(int));

    }

    WinTcpSocket::~WinTcpSocket()
    {
        closesocket(s);
    }

    bool WinTcpSocket::connect(const char *ip_addr, u_short port)
    {
        sockaddr_in addr;
        addr.sin_family = AF_INET;
        addr.sin_port = htons(port);
        inet_pton(AF_INET,ip_addr,&addr.sin_addr.s_addr);

        if (::connect(s,reinterpret_cast<sockaddr*>(&addr),sizeof(addr)))
        {
            std::cerr << "Connect failed." << std::endl;
            close();
            return false;
        }
        return true;
    }

    bool WinTcpSocket::send(const ClientResponse& message)
    {
        auto rawByte = static_cast<ClientResponse>(message);
        if (const int bytesSent = ::send(s,reinterpret_cast<const char*>(&rawByte), 1, 0); bytesSent == SOCKET_ERROR)
        {
            std::cerr << "Send failed." << std::endl;
            return false;
        }
        return true;
    }
    ServerCommand WinTcpSocket::receive()
    {
        uint8_t buffer;
        int bytesReceived = recv(s,reinterpret_cast<char*> (&buffer),1,0);

        if (bytesReceived == SOCKET_ERROR)
        {
            std::cerr << "Receive failed." << std::endl;
            return ServerCommand::Quit;
        }
        else if (bytesReceived == 0)
        {
            std::cerr << "Server disconnected." << std::endl;
            close();
            return ServerCommand::Quit;
        }
        return static_cast<ServerCommand>(buffer);
    }

    void WinTcpSocket::close()
    {
        closesocket(s);
    }
} // dd_rpi_backend