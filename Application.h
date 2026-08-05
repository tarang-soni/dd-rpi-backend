//
// Created by sonit on 05-08-2026.
//

#ifndef RPI_BACKEND_APPLICATION_H
#define RPI_BACKEND_APPLICATION_H
#include "TClientSocket.h"
#include <cstdint>

#include "NetworkManager.h"
#include "VideoStreamer.h"

namespace dd_rpi_backend
{
    class Application
    {

    public:
        Application();
        bool init();
        void run();
        void stop();

    private:
        void handleCommand(ServerCommand cmd);
    private:

        NetworkManager m_networkManager;
        VideoStreamer m_streamer;
        bool m_isRunning;
    };
}


#endif //RPI_BACKEND_APPLICATION_H