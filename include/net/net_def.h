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
        // Size of the network package in bytes.
        const Uint16 PACKAGE_BUFFER               = 4096;
        // Maximum number of clients a server can take.
        const Uint8  SERVER_MAX_CLIENTS           = 8;
        // Time to wait between two accept calls of a server in ms.
        const Uint16 SERVER_ACCEPT_WAIT_INTERVAL  = 100;
        // Time to wait between two resolve calls of a client in ms.
        const Uint16 CLIENT_RESOLVE_WAIT_INTERVAL = 100;

        enum class SOCKET_STATE
            : Uint8
        {
            CLOSED   = 0,
            IDLE     = 1,
            RESOLVED = 2,
            OPEN     = 3,
            BOUND    = 4
        };

        struct NetPackage
        {
            Uint32 package_id           = 0;
            bool   end_session          = false;
            Uint16 data[PACKAGE_BUFFER] = {0x0000};

            void print();
            void setData(Uint16 *data);
        };

        struct IPAddress
        {
            Uint32 host;
            Uint16 port;

            static std::string IPtoString(IPAddress ip);

            static std::string IPtoString(Uint32 ip);

            static Uint32 StringtoIP(std::string ip);

            static Uint16 StringtoPort(std::string port);

            static IPaddress toIPaddress(IPAddress ip);

            static IPAddress toIPAddress(IPaddress ip);
        };


    }
}

#endif //TURBO_NET_DEF_H
