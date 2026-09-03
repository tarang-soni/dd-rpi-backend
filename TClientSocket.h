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
    class TClientSocket
    {
        public:
        TClientSocket();
        virtual ~TClientSocket();

        virtual bool connect(const char* ip_addr,uint16_t port) = 0;

        virtual bool send(const ClientResponse& message) = 0;
        virtual const ServerCommand receive() =0;

        virtual void close() = 0;

        static std::unique_ptr<TClientSocket> create();

    };
} // dd_rpi_backend

#endif //RPI_BACKEND_TSOCKET_H