//
// Created by sonit on 05-08-2026.
//

#include "CommandListener.h"

#include <iostream>

#include "T_TCPSocket.h"

dd_rpi_backend::CommandListener::CommandListener():m_socket{nullptr}
{

}

bool dd_rpi_backend::CommandListener::connect(const std::string &host, uint16_t port)
{
    m_socket = T_TCPSocket::create();

    if (!m_socket->connect(host.c_str(), port))
    {
        std::cerr << "Failed to connect" << std::endl;
        return false;//fix this exit logic. retry instead of failed to connect
    }
    m_listening = true;
    return true;
}

void dd_rpi_backend::CommandListener::setCommandCallback(const CommandCallback &callback)
{
    m_onCommandReceived = callback;
}

void dd_rpi_backend::CommandListener::sendResponse(const ClientResponse response) const
{
    m_socket->send(response);
}

void dd_rpi_backend::CommandListener::listenLoop()
{
    std::cout << "Connected! Waiting for messages from server..." << std::endl;
    while (m_listening)
    {
        ServerCommand cmd = m_socket->receive();
        if (m_onCommandReceived)
        {
            m_onCommandReceived(cmd);
        }
        switch (cmd)
        {
            case ServerCommand::Quit:
                std::cout << "[Server]: Quit command received. Disconnecting." << std::endl;

                sendResponse(ClientResponse::ConnectionEnded);
                stop();
                break;
            case ServerCommand::StopStream:
                std::cout << "[Server]: Stop Stream command received." << std::endl;
                sendResponse(ClientResponse::StreamStopped);
                break;
            case ServerCommand::StartStream:
                std::cout << "[Server]: Start Stream command received." << std::endl;
                sendResponse(ClientResponse::StreamStarted);
                break;
            case ServerCommand::Ping:
                std::cout << "[Server]: Ping received." << std::endl;
                sendResponse(ClientResponse::Pong);
                break;
            case ServerCommand::Reboot:
                std::cout << "[Server]: Reboot command received." << std::endl;
                sendResponse(ClientResponse::StreamStarted);
                break;
            default:
                std::cout << "[Server]: Unknown command received." << std::endl;
                break;
        }
}


}

void dd_rpi_backend::CommandListener::stop()
{
    m_listening = false;
    m_socket->close();
}
