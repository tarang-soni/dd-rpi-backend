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
//UDP WORKFLOW
//start discovery server, and let it listen to port for commands.
//discovery will catch udp broadcast from pc
//this will now send a reply with its ip with an udp command
//pc will send an udp command now directly to this port to establish connection as pc is a server and this is a client
// will establish a connection through tcp protocol by starting commandlistener and connecting
void dd_rpi_backend::NetworkManager::startDiscovery(uint16_t port)
{
    m_discoveryServer.bind(port);//error handling here
    m_discoveryServer.setConnectCallback([this](const std::string &host,uint16_t port) {
        tcpConnect(host, port);
    });
    m_discoveryThread = std::thread(&DiscoveryServer::listenLoop,&m_discoveryServer);

}

void dd_rpi_backend::NetworkManager::stopDiscovery(uint16_t port)
{
    m_discoveryServer.stop();
    m_discoveryThread.join();
    //call discovery stop and then join the thread with main thread.
}



// void dd_rpi_backend::NetworkManager::start(const std::string &host, uint16_t port, CommandHandler handler)
// {
//     if (!m_commandListener.connect(host, port))
//     {
//         std::cerr<<"ERROR: Failed to connect to the server"<<std::endl;
//         return;
//     }
//
//     m_commandListener.setCommandCallback(handler);
//     m_commandThread = std::thread(&CommandListener::listenLoop, &m_commandListener);
//
// }
void dd_rpi_backend::NetworkManager::tcpConnect(const std::string &host, uint16_t port)
{
}
void dd_rpi_backend::NetworkManager::stop()
{
    if (m_commandThread.joinable())
    {
        m_commandThread.join();
        std::cout<<"Network thread joined and stopped"<<std::endl;
    }
    if (m_discoveryThread.joinable())
    {
        m_discoveryThread.join();
        std::cout<<"Discovery thread joined and stopped"<<std::endl;
    }
}

void dd_rpi_backend::NetworkManager::sendResponse(ClientResponse response)
{
    m_commandListener.sendResponse(response);
}

