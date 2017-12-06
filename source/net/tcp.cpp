#include "net/tcp.h"

namespace TURBO
{
    namespace NET
    {
        std::string IPAddress::IPtoString(IPAddress ip)
        {
            std::string ip_string;
            return "";
        }

        Uint32 IPAddress::StringtoIP(std::string ip)
        {
            Uint32 ip_address = 0x00000000;
            return ip_address;
        }

        IPaddress IPAddress::toIPaddress(IPAddress ip)
        {
            IPaddress ip_address;
            ip_address.host = ip.host;
            ip_address.port = ip.port;
            return ip_address;
        }

        IPAddress IPAddress::toIPAddress(IPaddress ip)
        {
            IPAddress ip_address;
            ip_address.host = ip.host;
            ip_address.port = ip.port;
            return ip_address;
        }

        ISocket::ISocket()
        {
            socket_state = SOCKET_STATE::IDLE;
        }

        NetPackage ISocket::getPackage()
        {
            return package;
        }

        void ISocket::setPackage(NetPackage package)
        {
            package = package;
        }

        SOCKET_STATE ISocket::getSocketState()
        {
            return socket_state;
        }

        bool ISocket::resolve(IPaddress & ip)
        {
            bool success = true;
            const char * host = NULL;
            ip = ip;

            if((host = SDLNet_ResolveIP(&ip)) == NULL)
            {
                success = false;
                UTIL::Log::err(SDLNet_GetError());
            }
            return success;
        }

        bool ISocket::resolve(std::string host, Uint16 port)
        {
            bool success = false;

            if(host == "")
            {
                if(SDLNet_ResolveHost(&ip, NULL, port) < 0)
                {
                    UTIL::Log::err(SDLNet_GetError());
                }
                else
                {
                    socket_state = SOCKET_STATE::RESOLVED;
                    success = true;
                }
            }
            else
            {
                if(SDLNet_ResolveHost(&ip, host.c_str(), port) < 0)
                {
                    UTIL::Log::err(SDLNet_GetError());
                }
                else
                {
                    socket_state = SOCKET_STATE::RESOLVED;
                    success = true;
                }
            }
            return success;
        }

        bool ISocket::isOpen()
        {
            bool success = false;

            if(socket_state >= SOCKET_STATE::OPEN)
            {
                success = true;
            }
            return success;
        }

        TCPsocket TCPSocket::getSocket()
        {
            return socket;
        }

        void TCPSocket::setSocket(TCPsocket socket)
        {
            socket = socket;
        }

        bool TCPSocket::open()
        {
            bool success = true;

            if(socket_state < SOCKET_STATE::OPEN && socket_state >= SOCKET_STATE::RESOLVED)
            {
                if((socket = SDLNet_TCP_Open(&ip)) == NULL)
                {
                    success = false;
                    UTIL::Log::err(SDLNet_GetError());
                }
                else
                {
                    socket_state = SOCKET_STATE::OPEN;
                }
            }
            return success;
        }

        bool TCPSocket::receive(NetPackage & package)
        {
            bool success = true;
            int result = SDLNet_TCP_Recv(socket, &package, sizeof(NetPackage));

            if(result <= 0)
            {
                success = false;
                UTIL::Log::err(SDLNet_GetError());
            }
            return success;
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
            bool success = true;

            int result = SDLNet_TCP_Send(socket, &package, sizeof(package));
            if(result < sizeof(package))
            {
                success = false;
                UTIL::Log::err(SDLNet_GetError());
            }
            return success;
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

        TCPClient::TCPClient(std::string host, Uint16 port)
        {
            resolve(host, port);
        }

        TCPServer::TCPServer(Uint16 port)
        {
            resolve("", port);
        }

        bool TCPServer::accept(TCPClient & client)
        {
            bool success = false;

            client.setSocket(SDLNet_TCP_Accept(socket));
            if(client.getSocket() == NULL)
            {
                success = false;
            }
            else
            {
                client_counter++;
                success = true;
            }
            return success;
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