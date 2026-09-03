//
// Created by sonit on 05-08-2026.
//

#include "Application.h"

#include <iostream>

dd_rpi_backend::Application::Application():m_isRunning{false}
{
}

bool dd_rpi_backend::Application::init()
{
    auto commandCallback = [this](ServerCommand cmd) {
        this->handleCommand(cmd);
    };
    m_networkManager.start("192.168.1.101",1234,commandCallback);
    m_isRunning = true;
    return true;
}

void dd_rpi_backend::Application::run()
{
    while (m_isRunning)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    std::cout << "Application loop exited." << std::endl;
    stop();
}

void dd_rpi_backend::Application::stop()
{
    std::cout << "Stopping application..." << std::endl;

    m_networkManager.stop();
}

void dd_rpi_backend::Application::handleCommand(ServerCommand cmd)
{
    switch (cmd)
    {
        case ServerCommand::StartStream:
            std::cout << "[App]: Instructing VideoStreamer to START." << std::endl;
            m_streamer.start("127.0.0.1",5000);

            break;

        case ServerCommand::StopStream:
            std::cout << "[App]: Instructing VideoStreamer to STOP." << std::endl;
            m_streamer.stop();
            break;

        case ServerCommand::Quit:
            std::cout << "[App]: Quit command received. Shutting down." << std::endl;
            m_streamer.stop();
            m_isRunning = false;
            break;

        default:
            break;
    }
}
