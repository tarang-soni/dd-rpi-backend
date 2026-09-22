//
// Created by sonit on 29-07-2026.
//
#ifndef RPI_BACKEND_TSOCKET_H
#define RPI_BACKEND_TSOCKET_H

#include <string>
#include <cstdint>
#include <memory>

#include "Protocols.h"

namespace dd_rpi_backend
{
    class T_TCPSocket
    {
        public:
        T_TCPSocket();
        virtual ~T_TCPSocket();

        virtual bool connect(const char* ip_addr,uint16_t port) = 0;

        virtual bool send(const ClientResponse& message) = 0;
        virtual ServerCommand receive() =0;

        virtual void close() = 0;

        static std::unique_ptr<T_TCPSocket> create();

    };
} // dd_rpi_backend

#endif //RPI_BACKEND_TSOCKET_H