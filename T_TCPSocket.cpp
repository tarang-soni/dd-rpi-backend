//
// Created by sonit on 29-07-2026.
//

#include "T_TCPSocket.h"

#if defined(_WIN32) || defined(_WIN64)
    #include "Platforms/Windows/WinTcpSocket.h"
#elif defined(__linux__)
    #include "Platforms/Linux/LinuxClientSocket.h"
#endif

namespace dd_rpi_backend
{

    T_TCPSocket::T_TCPSocket() = default;
    T_TCPSocket::~T_TCPSocket() = default;

    std::unique_ptr<T_TCPSocket> T_TCPSocket::create()
    {
#if defined(_WIN32) || defined(_WIN64)

        return std::make_unique<WinTcpSocket>();

#elif defined(__linux__)

        return std::make_unique<LinuxTcpSocket>();

#else

        throw std::runtime_error("Unsupported platform");

#endif
    }

} // namespace dd_rpi_backend