#include "../Windows/LinuxUDPSocket.h"
#include <iostream>
#include <cstring>
#include <cerrno>

namespace dd_rpi_backend
{
    LinuxUDPSocket::LinuxUDPSocket()
    {
        s = ::socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
        if (s < 0)
        {
            std::cerr << "UDP: Socket creation failed: " << std::strerror(errno) << std::endl;
        }
        else
        {
            // Enable broadcast permission on Linux (useful for discovery beacons)
            int broadcastEnable = 1;
            ::setsockopt(s, SOL_SOCKET, SO_BROADCAST, &broadcastEnable, sizeof(broadcastEnable));

            // Enable port reuse
            int reuse = 1;
            ::setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));
        }
    }

    LinuxUDPSocket::~LinuxUDPSocket()
    {
        close();
    }

    bool LinuxUDPSocket::bind(uint16_t port)
    {
        if (s < 0) return false;

        sockaddr_in addr{};
        addr.sin_family = AF_INET;
        addr.sin_addr.s_addr = htonl(INADDR_ANY);
        addr.sin_port = htons(port);

        int result = ::bind(s, reinterpret_cast<sockaddr*>(&addr), sizeof(addr));
        if (result < 0)
        {
            std::cerr << "UDP: Bind failed: " << std::strerror(errno) << std::endl;
            return false;
        }
        return true;
    }

    int LinuxUDPSocket::sendTo(const std::string &data, const std::string &ip, uint16_t port)
    {
        if (s < 0) return -1;

        std::cout << "Sending: " << data << '\n' << ip << ':' << port << '\n';

        sockaddr_in destination{};
        destination.sin_family = AF_INET;
        destination.sin_port = htons(port);

        if (inet_pton(AF_INET, ip.c_str(), &destination.sin_addr.s_addr) != 1)
        {
            std::cerr << "UDP: IP address not supported: " << ip << std::endl;
            return -1;
        }

        ssize_t bytesSent = ::sendto(
            s,
            data.data(),
            data.size(),
            0,
            reinterpret_cast<sockaddr*>(&destination),
            sizeof(destination)
        );

        if (bytesSent < 0)
        {
            std::cerr << "UDP: Send failed: " << std::strerror(errno) << std::endl;
            return -1;
        }
        return static_cast<int>(bytesSent);
    }

    bool LinuxUDPSocket::receiveFrom(std::string &data, std::string &senderIp, uint16_t &senderPort)
    {
        if (s < 0) return false;

        char buffer[1024];
        sockaddr_in sender{};
        socklen_t senderSize = sizeof(sender);

        ssize_t bytesReceived = ::recvfrom(
            s,
            buffer,
            sizeof(buffer),
            0,
            reinterpret_cast<sockaddr*>(&sender),
            &senderSize
        );

        if (bytesReceived < 0)
        {
            std::cerr << "UDP: Receive failed: " << std::strerror(errno) << std::endl;
            return false;
        }

        data.assign(buffer, bytesReceived);

        char ipBuffer[INET_ADDRSTRLEN];
        if (inet_ntop(AF_INET, &sender.sin_addr, ipBuffer, sizeof(ipBuffer)) == nullptr)
        {
            std::cerr << "inet_ntop failed: " << std::strerror(errno) << std::endl;
            return false;
        }

        senderIp = ipBuffer;
        senderPort = ntohs(sender.sin_port);
        return true;
    }

    void LinuxUDPSocket::close()
    {
        if (s >= 0)
        {
            ::close(s);
            s = -1;
        }
    }
} // namespace dd_rpi_backend