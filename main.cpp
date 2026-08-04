#include <iostream>
#include "TClientSocket.h"
#include <cstdint>
int main()
{
    //init winsock
    dd_rpi_backend::TClientSocket* socket = dd_rpi_backend::TClientSocket::create();

    if (!socket->connect("127.0.0.1", 1234))
    {
        std::cerr << "Failed to connect" << std::endl;
        return -1;
    }
    std::cout << "Connected! Waiting for messages from server..." << std::endl;
    while (true)
    {
        ServerCommand cmd = socket->receive();
        switch (cmd)
        {
            case ServerCommand::Quit:
                std::cout << "[Server]: Quit command received. Disconnecting." << std::endl;
                socket->send(ClientResponse::ConnectionEnded);
                socket->close();
                return 0; // Exit main loop

            case ServerCommand::StopStream:
                std::cout << "[Server]: Stop Stream command received." << std::endl;
                socket->send(ClientResponse::StreamStopped);
                break;

            case ServerCommand::StartStream:
                std::cout << "[Server]: Start Stream command received." << std::endl;
                socket->send(ClientResponse::StreamStarted);
                break;

            case ServerCommand::Ping:
                std::cout << "[Server]: Ping received." << std::endl;
                socket->send(ClientResponse::Pong);
                break;

            case ServerCommand::Reboot:
                std::cout << "[Server]: Reboot command received." << std::endl;
                // Handle reboot logic here if needed
                break;

            default:
                std::cout << "[Server]: Unknown command received." << std::endl;
                break;
        }
    }
}