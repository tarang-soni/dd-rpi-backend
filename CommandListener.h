//
// Created by sonit on 05-08-2026.
//

#ifndef RPI_BACKEND_COMMANDLISTENER_H
#define RPI_BACKEND_COMMANDLISTENER_H
#include <functional>
#include <memory>
#include "TClientSocket.h"
namespace dd_rpi_backend
{
    class CommandListener
    {
    public:
        using CommandCallback = std::function<void(ServerCommand)>;
        CommandListener();
        ~CommandListener() = default;

        bool connect(const std::string& host, uint16_t port);
        void setCommandCallback(const CommandCallback &callback);
        void sendResponse(ClientResponse response) const;
        void listenLoop();

    private:
        void stop();
    private:
        std::unique_ptr<TClientSocket> m_socket;
        CommandCallback m_onCommandReceived;
        bool m_listening{false};

    };
}
#endif //RPI_BACKEND_COMMANDLISTENER_H