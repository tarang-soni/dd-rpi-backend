#ifndef RPI_BACKEND_LINUXUDPSOCKET_H
#define RPI_BACKEND_LINUXUDPSOCKET_H

#include "T_UDPSocket.h"
#include <cstdint>
#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

namespace dd_rpi_backend
{
    class LinuxUDPSocket : public T_UDPSocket
    {
    public:
        LinuxUDPSocket();
        ~LinuxUDPSocket() override;

        bool bind(uint16_t port) override;
        int sendTo(const std::string& data, const std::string& ip, uint16_t port) override;
        bool receiveFrom(std::string& data, std::string& senderIp, uint16_t& senderPort) override;
        void close() override;

    private:
        int s;
    };
} // namespace dd_rpi_backend

#endif // RPI_BACKEND_LINUXUDPSOCKET_H