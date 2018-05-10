#ifndef TURBO_TCP_H
#define TURBO_TCP_H

#include "net/socket.h"

namespace TURBO
{
    namespace NET
    {
        class TCPSocket
            : public ISocket
        {
        protected:
            TCPsocket socket;

        public:
            virtual ~TCPSocket();

            IPaddress getPeerAddress();

            TCPsocket getSocket();

            void setSocket(TCPsocket socket);

            bool open() override;

            virtual bool receive(NetPackage &package);

            virtual NetPackage receive() override;

            bool send(NetPackage package) override;

            SOCKET_STATE close() override;
        };


        class TCPClient
            : public TCPSocket
        {
        protected:

        public:
            TCPClient();

            TCPClient(std::string host, Uint16 port);

            bool waitResolve(Sint32 max_wait = -1);
        };


        class TCPServer
            : public TCPSocket
        {
        protected:
            Uint8                    client_counter = 0;
            std::vector<TCPClient *> clients;

        public:
            explicit TCPServer(Uint16 port);

            ~TCPServer() override;

            bool accept(TCPClient &client);

            bool waitAccept(Uint8 clients = 1, Sint32 max_wait = -1);

            bool receive(NetPackage &package) override;

            NetPackage receive() override;

            bool send(NetPackage package) override;
        };

        class TCPServerSocketSet
            : public TCPSocket
        {
        protected:
            Uint8                    client_counter = 0;
            std::vector<TCPClient *> clients;
            SDLNet_SocketSet         socket_set;

        public:
            explicit TCPServerSocketSet(Uint8 clients, Uint16 port);

            ~TCPServerSocketSet() override;

            bool accept(TCPClient &client);

            Sint32 remove(Uint8 client);

            Sint32 checkClients(Uint32 max_wait = 1000);

            bool checkClient(Uint8 client);

            bool send(NetPackage package) override;
        };
    }
}
#endif //TURBO_TCP_H
