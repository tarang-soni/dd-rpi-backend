//
// Created by sonit on 29-07-2026.
//

#include "TClientSocket.h"

#if defined(_WIN32)|| defined(_WIN64)
#include "Platforms/Windows/WinClientSocket.h"
#endif
namespace dd_rpi_backend
{
    TClientSocket::TClientSocket() = default;
    TClientSocket::~TClientSocket() = default;

    TClientSocket* TClientSocket::create()
    {
        #if defined(_WIN32)|| defined(_WIN64)
        return new WinClientSocket();
        #endif
    }
} // dd_rpi_backend