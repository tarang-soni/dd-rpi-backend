//
// Created by sonit on 29-07-2026.
//

#include "WinClientSocket.h"

#include <iostream>
#include <ostream>

namespace dd_rpi_backend
{
    WinClientSocket::WinClientSocket()
    {
        WSADATA wsaData;
        if (WSAStartup(MAKEWORD(2,2),&wsaData)!=0)
        {
            std::cerr << "WSAStartup failed." << std::endl;
        }else
        {
            std::cerr << "WSAStartup success." << std::endl;
            s = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
        }

    }

    WinClientSocket::~WinClientSocket()
    {
        closesocket(s);
        WSACleanup();
    }

    bool WinClientSocket::connect(const char *ip_addr, u_short port)
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

    bool WinClientSocket::send(const ClientResponse& message)
    {
        auto rawByte = static_cast<ClientResponse>(message);
        if (const int bytesSent = ::send(s,reinterpret_cast<const char*>(&rawByte), 1, 0); bytesSent == SOCKET_ERROR)
        {
            std::cerr << "Send failed." << std::endl;
            return false;
        }
        return true;
    }

    const ServerCommand WinClientSocket::receive()
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

    void WinClientSocket::close()
    {
        closesocket(s);
    }
} // dd_rpi_backend