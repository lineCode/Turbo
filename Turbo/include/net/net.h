#ifndef NET_H_INCLUDED
#define NET_H_INCLUDED

#include "Turbo_main.h"
#include "utils/log.h"

namespace NET
{
    /**
    *** @enum SOCKET_STATE
    **/
    enum class SOCKET_STATE : Uint8
    {
        CLOSED  = 0,
        IDLE    = 1,
        OPEN    = 2,
        BOUND   = 3
    };


    struct IPAddress
    {
        Uint32      host;
        Uint16      port;

        static std::string IPtoString(IPAddress ip);
        static Uint32 StringtoIP(std::string ip);
        static IPaddress toIPaddress(IPAddress ip);
    };

    /**
    *** @class  ISocket
    ***
    *** @brief
    **/
    class ISocket
    {
    private:
        const std::string TAG = "ISocket";

    protected:
        SOCKET_STATE socket_state = SOCKET_STATE::CLOSED;

    public:
        ISocket();
        virtual bool        open() = 0;
        virtual std::string receive() = 0;
        virtual bool        send(std::string message) = 0;
        virtual void        close() = 0;
        virtual ~ISocket();
    };


    /**
    *** @class  TCPClient
    ***
    *** @brief
    **/
    class TCPClient : public ISocket
    {
    private:
        const std::string TAG = "TCPClient";

    protected:
        IPaddress client_ip;
        TCPsocket socket;

    public:
        TCPClient(std::string host, Uint16 port);
        TCPsocket   getSocket();
        bool        open();
        std::string receive();
        bool        send(std::string message);
        void        close();
        ~TCPClient();
    };


    /**
    *** @class  UDPClient
    ***
    *** @brief
    **/
    class UDPClient : ISocket
    {
    private:
        const std::string TAG = "UDPClient";

    protected:

    public:
        UDPClient();
        ~UDPClient();
    };


    /**
    *** @class  Server
    ***
    *** @brief
    **/
    class Server
    {
    private:
        const std::string TAG = "Server";

    protected:
        IPaddress ip;

    public:
        Server();
        ~Server();
    };


    /**
    *** @class  Client
    ***
    *** @brief
    **/
    class Client
    {
    private:
        const std::string TAG = "Client";

    protected:
        IPaddress ip;

    public:
        Client();
        ~Client();
    };

}

#endif // NET_H_INCLUDED
