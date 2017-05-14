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
        CLOSED      = 0,
        IDLE        = 1,
        RESOLVED    = 2,
        OPEN        = 3
    };


    /**
    *** @struct NetPackage
    ***
    *** @brief  This struct will contain all information of packages that will
    ***         be send over the network
    **/
    struct NetPackage
    {
        Uint16 data[TURBO::SDL_NET_BUFFER_LENGTH] = {0x0000};
    };


    /**
    *** @struct IPAddress
    **/
    struct IPAddress
    {
        Uint32      host;
        Uint16      port;

        static std::string IPtoString(IPAddress ip);
        static Uint32 StringtoIP(std::string ip);
        static IPaddress toIPaddress(IPAddress ip);
        static IPAddress toIPAddress(IPaddress ip);
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
        virtual NetPackage  receive() = 0;
        virtual bool        send(NetPackage package) = 0;
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
        IPaddress ip;
        TCPsocket socket = NULL;
        ///@TODO server clients std::vector<TCPClient *> clients;

    public:
        TCPClient();
        TCPClient(std::string host, Uint16 port);
        SOCKET_STATE    getSocketState();
        TCPsocket       getSocket();
        void            setSocket(TCPsocket socket);
        bool            resolve(IPaddress & ip);
        bool            resolve(std::string host, Uint16 port);
        bool            open();
        bool            isOpen();
        bool            accept(TCPClient & client);
        bool            receive(NetPackage & package);
        NetPackage      receive();
        bool            send(NetPackage package);
        void            close();
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

}

#endif // NET_H_INCLUDED
