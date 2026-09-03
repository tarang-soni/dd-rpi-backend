//
// Created by sonit on 29-07-2026.
//

#include "LinuxClientSocket.h"

#include <iostream>
#include <cstring>

namespace dd_rpi_backend
{

LinuxClientSocket::LinuxClientSocket()
{
    m_socket = socket(AF_INET, SOCK_STREAM, 0);

    if (m_socket == -1)
    {
        perror("socket");
        return;
    }

    int flag = 1;
    if (setsockopt(m_socket,
                   IPPROTO_TCP,
                   TCP_NODELAY,
                   &flag,
                   sizeof(flag)) == -1)
    {
        perror("setsockopt(TCP_NODELAY)");
    }
}

LinuxClientSocket::~LinuxClientSocket()
{
    close();
}

bool LinuxClientSocket::connect(const char *ip_addr, uint16_t port)
{
    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);

    if (inet_pton(AF_INET, ip_addr, &addr.sin_addr) <= 0)
    {
        perror("inet_pton");
        return false;
    }

    if (::connect(m_socket,
                  reinterpret_cast<sockaddr*>(&addr),
                  sizeof(addr)) < 0)
    {
        perror("connect");
        return false;
    }

    return true;
}

bool LinuxClientSocket::send(const ClientResponse &message)
{
    uint8_t rawByte = static_cast<uint8_t>(message);

    ssize_t bytesSent =
        ::send(m_socket,
               &rawByte,
               1,
               0);

    if (bytesSent != 1)
    {
        perror("send");
        return false;
    }

    return true;
}

ServerCommand LinuxClientSocket::receive()
{
    uint8_t buffer = 0;

    ssize_t bytesReceived =
        recv(m_socket,
             &buffer,
             1,
             0);

    if (bytesReceived < 0)
    {
        perror("recv");
        return ServerCommand::Quit;
    }

    if (bytesReceived == 0)
    {
        std::cerr << "Server disconnected." << std::endl;
        close();
        return ServerCommand::Quit;
    }

    return static_cast<ServerCommand>(buffer);
}

void LinuxClientSocket::close()
{
    if (m_socket != -1)
    {
        ::close(m_socket);
        m_socket = -1;
    }
}

} // namespace dd_rpi_backend