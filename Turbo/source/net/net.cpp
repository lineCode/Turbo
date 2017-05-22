#include "net/net.h"

using namespace NET;

string IPAddress::IPtoString(IPAddress ip)
{
    string ip_string = "";
    return 0;
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
    this->socket_state = SOCKET_STATE::IDLE;
}

NetPackage ISocket::getPackage()
{
    return this->package;
}

void ISocket::setPackage(NetPackage package)
{
    this->package = package;
}

SOCKET_STATE ISocket::getSocketState()
{
    return this->socket_state;
}

/**
 * @brief   Resolves to a host of the given ip address. If the host is reachable
 *          the ip member of the class gets all information
 * @param   ip
 */
bool ISocket::resolve(IPaddress & ip)
{
    bool success = true;
    const char * host = NULL;
    this->ip = ip;

    if((host = SDLNet_ResolveIP(&this->ip)) == NULL)
    {
        success = false;
        UTILS::Log::error(this->TAG, SDLNet_GetError(), UTILS::LOG_TYPE::ERROR);
    }
    return success;
}

/**
 * @brief   Resolves to the given host and port number. If the host is reachable
 *          the ip member of the class gets all information
 * @ref     SDLNet_ResolveHost
 * @param   host
 * @param   port
 */
bool ISocket::resolve(string host, Uint16 port)
{
    bool success = false;

    if(host == "")
    {
        if(SDLNet_ResolveHost(&this->ip, NULL, port) < 0)
        {
            UTILS::Log::error(this->TAG, SDLNet_GetError(), UTILS::LOG_TYPE::ERROR);
        }
        else
        {
            this->socket_state = SOCKET_STATE::RESOLVED;
            success = true;
        }
    }
    else
    {
        if(SDLNet_ResolveHost(&this->ip, host.c_str(), port) < 0)
        {
            UTILS::Log::error(this->TAG, SDLNet_GetError(), UTILS::LOG_TYPE::ERROR);
        }
        else
        {
            this->socket_state = SOCKET_STATE::RESOLVED;
            success = true;
        }
    }
    return success;
}

bool ISocket::isOpen()
{
    bool success = false;

    if(this->socket_state >= SOCKET_STATE::OPEN)
    {
        success = true;
    }
    return success;
}


ISocket::~ISocket()
{

}

TCPSocket::TCPSocket()
{

}

TCPsocket TCPSocket::getSocket()
{
    return this->socket;
}

void TCPSocket::setSocket(TCPsocket socket)
{
    this->socket = socket;
}

/**
 * @brief   Establishes a connection to the ip address of the ip member variable
 * @param
 */
bool TCPSocket::open()
{
    bool success = true;

    if(this->socket_state < SOCKET_STATE::OPEN && this->socket_state >= SOCKET_STATE::RESOLVED)
    {
        if((this->socket = SDLNet_TCP_Open(&this->ip)) == NULL)
        {
            success = false;
            UTILS::Log::error(this->TAG, SDLNet_GetError(), UTILS::LOG_TYPE::ERROR);
        }
        else
        {
            this->socket_state = SOCKET_STATE::OPEN;
        }
    }
    return success;
}

bool TCPSocket::receive(NetPackage & package)
{
    bool success = true;
    int result = SDLNet_TCP_Recv(this->socket, &package, sizeof(NetPackage));

    if(result <= 0)
    {
        success = false;
        UTILS::Log::error(this->TAG, SDLNet_GetError(), UTILS::LOG_TYPE::ERROR);
    }
    return success;
}

NetPackage TCPSocket::receive()
{
    NetPackage package;
    int result = SDLNet_TCP_Recv(this->socket, &package, sizeof(NetPackage));

    if(result <= 0)
    {
        UTILS::Log::error(this->TAG, SDLNet_GetError(), UTILS::LOG_TYPE::ERROR);
    }
    return package;
}

bool TCPSocket::send(NetPackage package)
{
    bool success = true;

    unsigned result = SDLNet_TCP_Send(this->socket, &package, sizeof(package));
    if(result < sizeof(package))
    {
        success = false;
        UTILS::Log::error(this->TAG, SDLNet_GetError(), UTILS::LOG_TYPE::ERROR);
    }
    return success;
}

void TCPSocket::close()
{
    if(this->socket_state >= SOCKET_STATE::OPEN)
    {
        SDLNet_TCP_Close(this->socket);
        this->socket_state  = SOCKET_STATE::CLOSED;
    }
}

TCPSocket::~TCPSocket()
{
    if(this->socket_state > SOCKET_STATE::CLOSED)
    {
        this->close();
    }
}

TCPClient::TCPClient()
{
}

TCPClient::TCPClient(string host, Uint16 port)
{
    this->resolve(host, port);
}

TCPClient::~TCPClient()
{

}


TCPServer::TCPServer(Uint16 port)
{
    this->resolve("", port);
}

/**
 * @brief   Accepts a connection to a client and binds the socket to the client.
 * @param
 */
bool TCPServer::accept(TCPClient & client)
{
    bool success = false;

    client.setSocket(SDLNet_TCP_Accept(this->socket));
    if(client.getSocket() == NULL)
    {
        success = false;
    }
    else
    {
        this->client_counter++;
        success = true;
    }
    return success;
}

TCPServer::~TCPServer()
{
    for(auto client : this->clients)
    {
        delete client;
    }
}

//UDPClient::UDPClient()
//{
//
//}
//
//UDPClient::~UDPClient()
//{
//
//}