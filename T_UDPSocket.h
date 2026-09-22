//
// Created by sonit on 22-09-2026.
//

#ifndef RPI_BACKEND_T_UDPSOCKET_H
#define RPI_BACKEND_T_UDPSOCKET_H
#include <cstdint>
#include <string>
#include <memory>
namespace dd_rpi_backend
{
    class T_UDPSocket
    {

    public:
        T_UDPSocket() = default;
        virtual ~T_UDPSocket() = default;
        virtual bool bind(uint16_t port) = 0;
        virtual int sendTo(const std::string& data,const std::string& ip,uint16_t port) = 0;
        virtual bool receiveFrom(std::string& data,std::string& senderIp,uint16_t& senderPort) = 0;
        virtual void close() = 0;
        static std::unique_ptr<T_UDPSocket> create();
    };
} // dd_rpi_backend

#endif //RPI_BACKEND_T_UDPSOCKET_H