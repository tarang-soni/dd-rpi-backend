//
// Created by sonit on 04-08-2026.
//

#ifndef RPI_BACKEND_UTILS_H
#define RPI_BACKEND_UTILS_H
#include <cstdint>
namespace dd_rpi_backend
{
    enum class ServerCommand:uint8_t{
        StartStream = 0x00,
        StopStream  = 0x01,
        Ping        = 0x02,
        Reboot      = 0x03,
        Quit        = 0x04
    };
    enum class ClientResponse:uint8_t{
        ConnectionSuccess = 0x10,
        StreamStarted     = 0x20,
        StreamStopped     = 0x30,
        ErrorDeviceBusy   = 0x40,
        Pong              = 0x50,
        ConnectionEnded   = 0x60
    };
}
#endif //RPI_BACKEND_UTILS_H