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
    this->socket_state = SOCKET_STATE::IDLE;
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
 * @brief   Resolves to a host of the given ip address. If the host is reachable
 *          the ip member of the class gets all information
 * @param   ip
 */
bool TCPSocket::resolve(IPaddress & ip)
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
 * @param   host
 * @param   port
 */
bool TCPSocket::resolve(string host, Uint16 port)
{
    bool success = true;

    if(host == "")
    {
        if(SDLNet_ResolveHost(&this->ip, NULL, port) < 0)
        {
            success = false;
            UTILS::Log::error(this->TAG, SDLNet_GetError(), UTILS::LOG_TYPE::ERROR);
        }
        else
        {
            this->socket_state = SOCKET_STATE::RESOLVED;
        }
    }
    else
    {
        if(SDLNet_ResolveHost(&this->ip, host.c_str(), port) < 0)
        {
            success = false;
            UTILS::Log::error(this->TAG, SDLNet_GetError(), UTILS::LOG_TYPE::ERROR);
        }
        else
        {
            this->socket_state = SOCKET_STATE::RESOLVED;
        }
    }
    return success;
}

/**
 * @brief   Establishes a connection to the ip address of the ip member variable
 * @param
 */
bool TCPSocket::open()
{
    bool success = true;

    if(this->socket_state < SOCKET_STATE::OPEN)
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

bool TCPSocket::stop()
{
    NetPackage package;
    package.end_session = true;
    this->send(package);
    return true;
}

TCPSocket::~TCPSocket()
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

void TCPServer::pollClient()
{
    while(0)
    {

    }
}

/**
 * @brief   Accepts a connection to a client and binds the socket to the client.
 * @param
 */
bool TCPServer::accept(TCPClient & client)
{
    bool success = false;

    //std::thread(&TCPServer::pollClient, this);
    client.setSocket(SDLNet_TCP_Accept(this->socket));
    if(client.getSocket() == NULL)
    {
        success = false;
    }
    return success;
}

TCPServer::~TCPServer()
{

}

TCPClient::TCPClient()
{
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