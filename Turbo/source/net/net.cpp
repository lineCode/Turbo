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

ISocket::ISocket()
{

}

ISocket::~ISocket()
{

}

TCPClient::TCPClient(string host, Uint16 port)
{
    if(host == "")
    {
        if(SDLNet_ResolveHost(&this->client_ip, NULL, port) < 0)
        {
            UTILS::Log::error(this->TAG, SDLNet_GetError(), UTILS::LOG_TYPE::ERROR);
        }
    }
    else
    {
        if(SDLNet_ResolveHost(&this->client_ip, host.c_str(), port) < 0)
        {
            UTILS::Log::error(this->TAG, SDLNet_GetError(), UTILS::LOG_TYPE::ERROR);
        }
    }
}

TCPsocket TCPClient::getSocket()
{
    return this->socket;
}

bool TCPClient::open()
{
    bool success = true;

    if((this->socket = SDLNet_TCP_Open(&this->client_ip)) == NULL)
    {
        success = false;
        UTILS::Log::error(this->TAG, SDLNet_GetError(), UTILS::LOG_TYPE::ERROR);
    }
    return success;
}

string TCPClient::receive()
{
    string message = "";
    char buffer[TURBO::SDL_NET_BUFFER_LENGTH];
    int result = SDLNet_TCP_Recv(this->socket, buffer, TURBO::SDL_NET_BUFFER_LENGTH);

    if(result <= 0)
    {
        UTILS::Log::error(this->TAG, SDLNet_GetError(), UTILS::LOG_TYPE::ERROR);
    }
    message = buffer;
    return message;
}

bool TCPClient::send(string message)
{
    bool success = true;
    //const char * m = message.c_str();
    //const char * m = "asdasdasd";
    unsigned result = SDLNet_TCP_Send(this->socket, &message, message.size());
    if(result < message.length())
    {
        success = false;
        UTILS::Log::error(this->TAG, SDLNet_GetError(), UTILS::LOG_TYPE::ERROR);
    }
    return success;
}

void TCPClient::close()
{
    SDLNet_TCP_Close(this->socket);
}

TCPClient::~TCPClient()
{

}

UDPClient::UDPClient()
{

}

UDPClient::~UDPClient()
{

}

Server::Server()
{

}

Server::~Server()
{

}

Client::Client()
{

}

Client::~Client()
{

}
