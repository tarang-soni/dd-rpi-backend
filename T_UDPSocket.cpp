//
// Created by sonit on 22-09-2026.
//

#include "T_UDPSocket.h"

#include <memory>

#if defined(_WIN32) || defined(_WIN64)
#include "WinUDPSocket.h"
#elif defined(__linux__)
#include "LinuxUDPSocket.h"
#endif

namespace dd_rpi_backend
{
    std::unique_ptr<T_UDPSocket> T_UDPSocket::create()
    {
#if defined(_WIN32) || defined(_WIN64)
        return std::make_unique<WinUDPSocket>();
#elif defined(__linux__)
        return std::make_unique<LinuxUDPSocket>
#else

        throw std::runtime_error("Unsupported platform");

#endif
    }
} // dd_rpi_backend