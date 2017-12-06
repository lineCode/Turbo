#ifndef TURBO_NET_DEF_H
#define TURBO_NET_DEF_H

#include <iostream>
#include <vector>

#include <SDL_types.h>
#include <SDL_net.h>

#include "turbo_def.h"
#include "util/log.h"

namespace TURBO
{
    namespace NET
    {
        const Uint16 MAX_NET_BUFFER = 4096;

        enum class SOCKET_STATE : Uint8
        {
            CLOSED      = 0,
            IDLE        = 1,
            RESOLVED    = 2,
            OPEN        = 3,
            BOUND       = 4
        };

        struct NetPackage
        {
            Uint32  package_id = 0;
            bool    end_session = false;
            Uint16  data[MAX_NET_BUFFER] = {0x0000};
        };

        struct IPAddress
        {
            Uint32      host;
            Uint16      port;

            static std::string IPtoString(IPAddress ip);
            static Uint32 StringtoIP(std::string ip);
            static IPaddress toIPaddress(IPAddress ip);
            static IPAddress toIPAddress(IPaddress ip);
        };

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

#endif //TURBO_NET_DEF_H
