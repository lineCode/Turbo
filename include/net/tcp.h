#ifndef TURBO_TCP_H
#define TURBO_TCP_H

#include "net/net_def.h"

namespace TURBO
{
    namespace NET
    {
        class TCPSocket : public ISocket
        {
        protected:
            TCPsocket socket = NULL;

        public:
            virtual ~TCPSocket();
            virtual TCPsocket       getSocket();
            virtual void            setSocket(TCPsocket socket);
            virtual bool            open();
            virtual bool            receive(NetPackage & package);
            virtual NetPackage      receive();
            virtual bool            send(NetPackage package);
            virtual void            close();
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
            ~TCPServer();
            bool accept(TCPClient & client);
        };
    }
}
#endif //TURBO_TCP_H
