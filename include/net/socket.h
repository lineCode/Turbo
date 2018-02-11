#ifndef TURBO_SOCKET_H
#define TURBO_SOCKET_H

#include "net/net_def.h"

namespace TURBO
{
    namespace NET
    {
        class ISocket
        {
        protected:
            SOCKET_STATE    socket_state = SOCKET_STATE::CLOSED;
            NetPackage      package;
            IPaddress       ip;

        public:
            ISocket();
            virtual NetPackage      getPackage();
            virtual void            setPackage(NetPackage package);
            virtual SOCKET_STATE    getSocketState();
            virtual bool            open() = 0;
            virtual NetPackage      receive() = 0;
            virtual bool            send(NetPackage package) = 0;
            virtual void            close() = 0;
            virtual bool            isOpen();
            virtual bool            resolve(IPaddress & ip);
            virtual bool            resolve(std::string host, Uint16 port);
        };
    }
}

#endif //TURBO_SOCKET_H
