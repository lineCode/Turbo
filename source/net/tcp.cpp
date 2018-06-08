#include <SDL_net.h>
#include "net/tcp.h"

namespace TURBO
{
    namespace NET
    {
        IPaddress TCPSocket::getPeerAddress()
        {
            return *SDLNet_TCP_GetPeerAddress(socket);
        }

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
                    return true;
                }
            }
            else
            {
                return false;
            }
        }

        bool TCPSocket::receive(NetPackage &package)
        {
            if(socket_state >= SOCKET_STATE::OPEN)
            {
                int result = SDLNet_TCP_Recv(socket, &package, sizeof(NetPackage));

                if(result < 0)
                {
                    std::string err = "Socket receive: ";
                    UTIL::Log::err(err + SDLNet_GetError());
                    return false;
                }
                else if(result == 0)
                {
                    // no bytes received
                }
                return true;
            }
            return false;
        }

        NetPackage TCPSocket::receive()
        {
            NetPackage package = {};
            if(socket_state >= SOCKET_STATE::OPEN)
            {
                int result = SDLNet_TCP_Recv(socket, &package, sizeof(NetPackage));

                if(result < 0)
                {
                    std::string err = "Socket receive: ";
                    UTIL::Log::err(err + SDLNet_GetError());
                }
                else if(result == 0)
                {
                    // no bytes received
                }
            }
            return package;
        }

        bool TCPSocket::send(NetPackage package)
        {
            if(socket_state >= SOCKET_STATE::OPEN)
            {
                int result = SDLNet_TCP_Send(socket, &package, sizeof(package));
                if(result < sizeof(package))
                {
                    UTIL::Log::err(SDLNet_GetError());
                    return false;
                }
                else
                {
                    // not enough bytes send
                }
                return true;
            }
            return false;
        }

        SOCKET_STATE TCPSocket::close()
        {
            if(socket_state >= SOCKET_STATE::OPEN)
            {
                SDLNet_TCP_Close(socket);
                socket_state = SOCKET_STATE::CLOSED;
            }
            return socket_state;
        }

        TCPSocket::~TCPSocket()
        {
            if(socket_state > SOCKET_STATE::CLOSED)
            {
                close();
            }
        }

        TCPClient::TCPClient()
        {

        }

        TCPClient::TCPClient(const std::string host, Uint16 port)
        {
            resolve(host, port);
            open();
        }

        /**
         * Tries to connect to a server. Returns false when the maximum retry time is reached.
         * @param max_wait the maximum wait time in milliseconds (-1 will try forever)
         * @return
         */
        bool TCPClient::waitResolve(Sint32 max_wait)
        {
            Uint32 ticks = SYSTEM::Clock::getTicks();
            while(!resolve(IPAddress::IPtoString(ip.host), ip.port))
            {
                if(max_wait > 0)
                {
                    if(SYSTEM::Clock::getTicks() > ticks + max_wait)
                    {
                        return false;
                    }
                }
                SDL_Delay(CLIENT_RESOLVE_WAIT_INTERVAL);
            }
            open();
            return true;
        }

        TCPServer::TCPServer(Uint16 port)
        {
            resolve("", port);
            open();
        }

        TCPServer::~TCPServer()
        {
            for(auto & client : clients)
            {
                client->~TCPSocket();
            }
            this->~TCPSocket();
        }

        bool TCPServer::accept(TCPClient &client)
        {
            if(socket_state >= SOCKET_STATE::OPEN)
            {
                client.setSocket(SDLNet_TCP_Accept(socket));
                if(client.getSocket() == nullptr)
                {
                    return false;
                }
                else
                {
                    clients.push_back(&client);
                    client_counter++;
                    return true;
                }
            }
            return false;
        }

        /**
         * Tries to accept a number of clients.
         * @param client_number the number of clients the server will allow to connect
         * @param max_wait the maximum wait time in milliseconds (-1 will try forever)
         * @return
         */
        bool TCPServer::waitAccept(Uint8 client_number, Sint32 max_wait)
        {
            if(client_number < SERVER_MAX_CLIENTS)
            {
                Uint32    ticks   = SYSTEM::Clock::getTicks();
                TCPClient *client = new TCPClient();
                while(clients.size() < client_number)
                {
                    if(accept(*client))
                    {
                        client = new TCPClient();
                    }
                    if(max_wait > 0)
                    {
                        if(SYSTEM::Clock::getTicks() > ticks + max_wait)
                        {
                            return false;
                        }
                    }
                    SDL_Delay(SERVER_ACCEPT_WAIT_INTERVAL);
                }
                return true;
            }
            else
            {
                UTIL::Log::err("Server can only take " + std::to_string(SERVER_MAX_CLIENTS) + " clients");
                return false;
            }
        }

        bool TCPServer::receive(NetPackage &package)
        {
            if(socket_state >= SOCKET_STATE::OPEN)
            {
                int index = 0;
                for(const auto &client : clients)
                {
                    int result = SDLNet_TCP_Recv(client->getSocket(), &package, sizeof(NetPackage));
                    if(result < sizeof(package))
                    {
                        UTIL::Log::err(SDLNet_GetError());
                        return false;
                    }
                    else
                    {
                        // no bytes received
                    }
                    index++;
                }
            }
            return true;
        }

        NetPackage TCPServer::receive()
        {
            NetPackage package{};
            NetPackage packages[client_counter]{};
            if(socket_state >= SOCKET_STATE::OPEN)
            {
                int index = 0;
                for(const auto &client : clients)
                {
                    int result = SDLNet_TCP_Recv(client->getSocket(), &packages[index], sizeof(NetPackage));
                    if(result < sizeof(package))
                    {
                        UTIL::Log::err(SDLNet_GetError());
                        return package;
                    }
                    else
                    {
                        // no bytes received
                    }
                    index++;
                }
            }
            return package;
        };

        bool TCPServer::send(NetPackage package)
        {
            if(socket_state >= SOCKET_STATE::OPEN)
            {
                for(const auto &client : clients)
                {
                    int result = SDLNet_TCP_Send(client->getSocket(), &package, sizeof(package));
                    if(result < sizeof(package))
                    {
                        UTIL::Log::err(SDLNet_GetError());
                        return false;
                    }
                    else
                    {
                        // not enough bytes send
                    }
                }
                return true;
            }
            return false;
        }

        TCPServerSocketSet::TCPServerSocketSet(Uint8 clients, Uint16 port)
        {
            resolve(ip);
            open();

            socket_set = SDLNet_AllocSocketSet(clients);
        }

        TCPServerSocketSet::~TCPServerSocketSet()
        {
            SDLNet_FreeSocketSet(socket_set);
            for(auto & client : clients)
            {
                client->~TCPSocket();
            }
            this->~TCPSocket();
        }

        bool TCPServerSocketSet::accept(NET::TCPClient &client)
        {
            if(socket_state >= SOCKET_STATE::OPEN)
            {
                int client_num = SDLNet_TCP_AddSocket(socket_set, client.getSocket());
                if(client_num < 0)
                {
                    UTIL::Log::err(SDLNet_GetError());
                    return false;
                }
                else
                {
                    clients.push_back(&client);
                    client_counter++;
                    return true;
                }
            }
            return false;
        }

        Sint32 TCPServerSocketSet::remove(Uint8 client)
        {
            if(socket_state >= SOCKET_STATE::OPEN)
            {
                int client_num = SDLNet_TCP_DelSocket(socket_set, clients.at(client)->getSocket());
                if(client_num < 0)
                {
                    UTIL::Log::err(SDLNet_GetError());
                    return client_num;
                }
                else
                {
                    return client_num;
                }
            }
            return 0;
        }

        Sint32 TCPServerSocketSet::checkClients(Uint32 max_wait)
        {
            if(socket_state >= SOCKET_STATE::OPEN)
            {
                int client_num = SDLNet_CheckSockets(socket_set, max_wait);
                if(client_num < 0)
                {
                    UTIL::Log::err(SDLNet_GetError());
                    return client_num;
                }
                else
                {
                    return client_num;
                }
            }
            return 0;
        }

        bool TCPServerSocketSet::checkClient(Uint8 client)
        {
            return SDLNet_SocketReady(clients.at(client)->getSocket()) > 0;
        }

        bool TCPServerSocketSet::send(NET::NetPackage package)
        {
            return TCPSocket::send(package);
        }
    }
}