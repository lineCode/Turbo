#ifndef TURBO_SOCKET_H
#define TURBO_SOCKET_H

#include "net/net_def.h"
#include "util/string.h"

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
            virtual IPaddress       getIPaddress();
            virtual NetPackage      getPackage();
            virtual void            setPackage(NetPackage package);
            virtual SOCKET_STATE    getSocketState();
            virtual bool            open() = 0;
            virtual NetPackage      receive() = 0;
            virtual bool            send(NetPackage package) = 0;
            virtual SOCKET_STATE    close() = 0;
            virtual bool            isOpen();
            virtual bool            isResolved();
            virtual bool            resolve(IPaddress & ip);
            virtual bool            resolve(std::string host, Uint16 port);
        };
    }
}

#endif //TURBO_SOCKET_H
