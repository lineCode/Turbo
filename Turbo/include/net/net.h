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
        OPEN        = 3,
        BOUND       = 4
    };


    /**
    *** @struct NetPackage
    ***
    *** @brief  This struct will contain all information of packages that will
    ***         be send over the network
    **/
    struct NetPackage
    {
        Uint32  package_id = 0;
        bool    end_session = false;
        Uint16  data[TURBO::SDL_NET_BUFFER_LENGTH] = {0x0000};
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
        SOCKET_STATE    socket_state = SOCKET_STATE::CLOSED;
        NetPackage      package;
        IPaddress       ip;

    public:
        ISocket();
                NetPackage      getPackage();
                void            setPackage(NetPackage package);
                SOCKET_STATE    getSocketState();
        virtual bool            open() = 0;
        virtual NetPackage      receive() = 0;
        virtual bool            send(NetPackage package) = 0;
        virtual void            close() = 0;
        virtual bool            isOpen();
        virtual ~ISocket();
    };

    /**
    *** @class  TCPSocket
    ***
    *** @brief
    **/
    class TCPSocket : public ISocket
    {
    private:
        const std::string TAG = "TCPSocket";

    protected:
        TCPsocket socket;

    public:
        TCPSocket();
        TCPsocket       getSocket();
        void            setSocket(TCPsocket socket);
        bool            resolve(IPaddress & ip);
        bool            resolve(std::string host, Uint16 port);
        bool            open();
        bool            receive(NetPackage & package);
        NetPackage      receive();
        bool            send(NetPackage package);
        void            close();
        bool            stop();
        ~TCPSocket();
    };


    /**
    *** @class  TCPClient
    ***
    *** @brief
    **/
    class TCPClient : public TCPSocket
    {
    private:
        const std::string TAG = "TCPClient";

    protected:

    public:
        TCPClient();
        TCPClient(std::string host, Uint16 port);
        ~TCPClient();
    };


    /**
    *** @class  TCPServer
    ***
    *** @brief
    **/
    class TCPServer : public TCPSocket
    {
    private:
        const std::string TAG = "TCPServer";

        void pollClient();

    protected:
        std::vector<TCPClient *> clients;

    public:
        TCPServer(Uint16 port);
        bool            accept(TCPClient & client);
        ~TCPServer();
    };


    /**
    *** @class  UDPSocket
    ***
    *** @brief
    **/
    /*
    class UDPSocket : public ISocket
    {
    private:
        const std::string TAG = "UDPSocket";

    protected:

    public:
        UDPSocket();
        ~UDPSocket();
    };*/

}

#endif // NET_H_INCLUDED
