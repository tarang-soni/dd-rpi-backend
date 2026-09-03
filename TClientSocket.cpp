//
// Created by sonit on 29-07-2026.
//

#include "TClientSocket.h"

#if defined(_WIN32) || defined(_WIN64)
    #include "Platforms/Windows/WinClientSocket.h"
#elif defined(__linux__)
    #include "Platforms/Linux/LinuxClientSocket.h"
#endif

namespace dd_rpi_backend
{

    TClientSocket::TClientSocket() = default;
    TClientSocket::~TClientSocket() = default;

    std::unique_ptr<TClientSocket> TClientSocket::create()
    {
#if defined(_WIN32) || defined(_WIN64)

        return std::make_unique<WinClientSocket>();

#elif defined(__linux__)

        return std::make_unique<LinuxClientSocket>();

#else

        throw std::runtime_error("Unsupported platform");

#endif
    }

} // namespace dd_rpi_backend