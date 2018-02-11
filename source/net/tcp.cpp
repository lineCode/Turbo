#include "net/tcp.h"

namespace TURBO
{
    namespace NET
    {
        TCPsocket TCPSocket::getSocket()
        {
            return socket;
        }

        void TCPSocket::setSocket(TCPsocket socket)
        {
            this->socket = socket;
        }

        bool TCPSocket::open()
        {
            if(socket_state < SOCKET_STATE::OPEN && socket_state >= SOCKET_STATE::RESOLVED)
            {
                if((socket = SDLNet_TCP_Open(&ip)) == nullptr)
                {
                    UTIL::Log::err(SDLNet_GetError());
                    return false;
                }
                else
                {
                    socket_state = SOCKET_STATE::OPEN;
                }
            }
            return true;
        }

        bool TCPSocket::receive(NetPackage & package)
        {
            int result = SDLNet_TCP_Recv(socket, &package, sizeof(NetPackage));

            if(result <= 0)
            {
                UTIL::Log::err(SDLNet_GetError());
                return false;
            }
            return true;
        }

        NetPackage TCPSocket::receive()
        {
            NetPackage package;
            int result = SDLNet_TCP_Recv(socket, &package, sizeof(NetPackage));

            if(result <= 0)
            {
                UTIL::Log::err(SDLNet_GetError());
            }
            return package;
        }

        bool TCPSocket::send(NetPackage package)
        {
            int result = SDLNet_TCP_Send(socket, &package, sizeof(package));
            if(result < sizeof(package))
            {
                UTIL::Log::err(SDLNet_GetError());
                return false;
            }
            return true;
        }

        void TCPSocket::close()
        {
            if(socket_state >= SOCKET_STATE::OPEN)
            {
                SDLNet_TCP_Close(socket);
                socket_state  = SOCKET_STATE::CLOSED;
            }
        }

        TCPSocket::~TCPSocket()
        {
            if(socket_state > SOCKET_STATE::CLOSED)
            {
                close();
            }
        }

        TCPClient::TCPClient(const std::string host, Uint16 port)
        {
            resolve(host, port);
        }

        TCPServer::TCPServer(Uint16 port)
        {
            resolve("", port);
        }

        bool TCPServer::accept(TCPClient & client)
        {
            client.setSocket(SDLNet_TCP_Accept(socket));
            if(client.getSocket() == nullptr)
            {
                return false;
            }
            else
            {
                client_counter++;
                return true;
            }
        }

        TCPServer::~TCPServer()
        {
            for(auto client : clients)
            {
                delete client;
            }
            this->~TCPSocket();
        }
    }
}