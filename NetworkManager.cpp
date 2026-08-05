//
// Created by sonit on 05-08-2026.
//

#include "NetworkManager.h"

#include <iostream>
#include <ostream>

dd_rpi_backend::NetworkManager::NetworkManager()
{
}

dd_rpi_backend::NetworkManager::~NetworkManager()
{
    stop();
}

void dd_rpi_backend::NetworkManager::start(const std::string &host, uint16_t port, CommandHandler handler)
{
    if (!m_commandListener.connect(host, port))
    {
        std::cerr<<"ERROR: Failed to connect to the server"<<std::endl;
        return;
    }
    m_commandListener.setCommandCallback(handler);
    m_listenerThread = std::thread(&CommandListener::listenLoop, &m_commandListener);
}

void dd_rpi_backend::NetworkManager::stop()
{
    if (m_listenerThread.joinable())
    {
        m_listenerThread.join();
        std::cout<<"Network thread joined and stopped"<<std::endl;
    }
}

void dd_rpi_backend::NetworkManager::sendResponse(ClientResponse response)
{
    m_commandListener.sendResponse(response);
}
