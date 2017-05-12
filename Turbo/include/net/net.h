#ifndef NET_H_INCLUDED
#define NET_H_INCLUDED

#include "Turbo_main.h"

namespace NET
{
    class Server
    {
    private:
        IPaddress ip;
        
    public:
        Server();
        ~Server();
    };

    class Client
    {
    private:
        IPaddress ip;

    public:
        Client();
        ~Client();
    };
}

#endif // NET_H_INCLUDED
