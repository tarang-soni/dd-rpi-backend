#ifndef RPI_BACKEND_LINUXCLIENTSOCKET_H
#define RPI_BACKEND_LINUXCLIENTSOCKET_H

#include "T_TCPSocket.h"
#include "Protocols.h"

#include <arpa/inet.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>

namespace dd_rpi_backend
{

    class LinuxTcpSocket : public T_TCPSocket
    {
    public:
        LinuxTcpSocket();
        ~LinuxTcpSocket() override;

        bool connect(const char* ip_addr, uint16_t port) override;

        bool send(const ClientResponse& message) override;
        ServerCommand receive() override;

        void close() override;

    private:
        int m_socket = -1;
    };

} // namespace dd_rpi_backend

#endif