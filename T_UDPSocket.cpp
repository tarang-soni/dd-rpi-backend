//
// Created by sonit on 22-09-2026.
//

#include "T_UDPSocket.h"

#include <memory>

#include "WinUDPSocket.h"

namespace dd_rpi_backend
{
    std::unique_ptr<T_UDPSocket> T_UDPSocket::create()
    {
#if defined(_WIN32) || defined(_WIN64)
        return std::make_unique<WinUDPSocket>();
#endif

    }
} // dd_rpi_backend