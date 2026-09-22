//
// Created by sonit on 22-09-2026.
//

#include "WinUDPSocket.h"
#include <iostream>
namespace dd_rpi_backend
{
    WinUDPSocket::WinUDPSocket()
    {
        s = socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
    }

    WinUDPSocket::~WinUDPSocket()
    {
        closesocket(s);
    }

    bool WinUDPSocket::bind(uint16_t port)
    {
        sockaddr_in addr{};
        addr.sin_family = AF_INET;
        addr.sin_addr.s_addr = htonl(INADDR_ANY);
        addr.sin_port = htons(port);
        int result = ::bind(s, reinterpret_cast<sockaddr*>(&addr), sizeof(addr));
        if (result == SOCKET_ERROR)
        {
            std::cerr << "UDP: Bind failed: "
                      << WSAGetLastError()
                      << std::endl;
            return false;
        }
        return true;
    }

    int WinUDPSocket::sendTo(const std::string &data, const std::string &ip, uint16_t port)
    {
        std::cout << "sendTo called\n";
        return 0;
    }

    bool WinUDPSocket::receiveFrom(std::string &data, std::string &senderIp, uint16_t &senderPort)
    {
        char buffer[1024];
        sockaddr_in sender{};
        int senderSize = sizeof(sender);

        int bytesReceived = recvfrom(s, buffer, sizeof(buffer), 0, reinterpret_cast<sockaddr*>(&sender), &senderSize);
        if (bytesReceived == SOCKET_ERROR)
        {
            std::cerr << "UDP: Receive failed: " << WSAGetLastError() << std::endl;
            return false;
        }
        data.assign(buffer, bytesReceived);
        char ipBuffer[INET_ADDRSTRLEN];

        if (inet_ntop(AF_INET,
                      &sender.sin_addr,
                      ipBuffer,
                      sizeof(ipBuffer)) == nullptr)
        {
            std::cerr << "inet_ntop failed: " << WSAGetLastError() << std::endl;
            return false;
        }

        senderIp = ipBuffer;
        senderPort = ntohs(sender.sin_port);
        return true;
    }

    void WinUDPSocket::close()
    {
    }
} // dd_rpi_backend