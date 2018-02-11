#ifndef TURBO_TCP_H
#define TURBO_TCP_H

#include "net/socket.h"

namespace TURBO
{
    namespace NET
    {
        class TCPSocket : public ISocket
        {
        protected:
            TCPsocket socket;

        public:
            virtual ~TCPSocket();
            TCPsocket       getSocket();
            void            setSocket(TCPsocket socket);
            bool            open() override;
            bool            receive(NetPackage & package);
            NetPackage      receive() override;
            bool            send(NetPackage package) override;
            void            close() override;
        };


        class TCPClient : public TCPSocket
        {
        protected:

        public:
            TCPClient(std::string host, Uint16 port);
        };


        class TCPServer : public TCPSocket
        {
        protected:
            Uint16                      client_counter = 0;
            std::vector<TCPClient *>    clients;

        public:
            explicit TCPServer(Uint16 port);
            ~TCPServer() override;
            bool accept(TCPClient & client);
        };
    }
}
#endif //TURBO_TCP_H
