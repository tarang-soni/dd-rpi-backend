//
// Created by sonit on 22-09-2026.
//

#include "DiscoveryServer.h"
#include <string>
#include  <iostream>
namespace dd_rpi_backend
{
    void DiscoveryServer::bind(const uint16_t port)
    {
        //use factory to create udp just like we did in tcp
        m_udp = T_UDPSocket::create();
        if (!m_udp->bind(port))
        {
            std::cerr << "Failed to bind UDP socket\n";
            return;
        }else
        {
            m_listening = true;
            std::cout << "Started Discovery service on UDP Port: " << port << '\n';
        }


    }

    void DiscoveryServer::stop()
    {
        m_listening = false;
        m_udp->close();

    }

    void DiscoveryServer::listenLoop()
    {
        std::cout << "listenLoop started\n";
        while (m_listening)
        {
            std::string data;
            std::string ip;
            uint16_t port;
            if (m_udp->receiveFrom(data,ip,port))
            {
                if (data == "DD_DISCOVERY")
                {
                    //m_udp->sendTo("DD_REPLY", ip, port);
                    std::cout << "Received: " << data << '\n';
                    std::cout << "From: " << ip << ":" << port << '\n';
                }
            }
        }
    }

    void DiscoveryServer::processDiscoveryRequest()
    {
    }

    void DiscoveryServer::sendReply()
    {
    }
} // dd_rpi_backend