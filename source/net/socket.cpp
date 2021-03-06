#include "net/socket.h"

namespace TURBO
{
    namespace NET
    {
        void NetPackage::print()
        {
            for(const auto & c : data)
            {
                std::cout << UTIL::toUnicode(c);
            }

            std::cout << "\n";
        }

        void NetPackage::setData(Uint16 *data)
        {

        }

        std::string IPAddress::IPtoString(IPAddress ip)
        {
            std::stringstream ss;
            ss << static_cast<int>((ip.host & 0x00FF0000) >> 24)
               << "."
               << static_cast<int>((ip.host & 0x00FF0000) >> 16)
               << "."
               << static_cast<int>((ip.host & 0x0000FF00) >> 8)
               << "."
               << static_cast<int>(ip.host & 0x000000FF)
               << ":"
               << ip.port;
            return ss.str();
        }

        std::string IPAddress::IPtoString(Uint32 ip)
        {
            std::stringstream ss;
            ss << static_cast<int>((ip & 0x00FF0000) >> 24)
               << "."
               << static_cast<int>((ip & 0x00FF0000) >> 16)
               << "."
               << static_cast<int>((ip & 0x0000FF00) >> 8)
               << "."
               << static_cast<int>(ip & 0x000000FF)
               << ":";
            return ss.str();
        }

        Uint32 IPAddress::StringtoIP(std::string ip)
        {
            char              c          = 0;
            int               o1         = 0, o2 = 0, o3 = 0, o4 = 0;
            Uint32            ip_address = 0x00000000;
            std::stringstream ss(ip);
            ss >> o1 >> c >> o2 >> c >> o3 >> c >> o4;
            ip_address += (o1 << 24);
            ip_address += (o2 << 16);
            ip_address += (o3 << 8);
            ip_address += o4;
            return ip_address;
        }

        Uint16 IPAddress::StringtoPort(std::string port)
        {
            std::stringstream ss(port);
            Uint16            ip_port = 0x0000;
            ss >> ip_port;
            return ip_port;
        }

        IPaddress IPAddress::toIPaddress(IPAddress ip)
        {
            IPaddress ip_address = {};
            ip_address.host = ip.host;
            ip_address.port = ip.port;
            return ip_address;
        }

        IPAddress IPAddress::toIPAddress(IPaddress ip)
        {
            IPAddress ip_address = {};
            ip_address.host = ip.host;
            ip_address.port = ip.port;
            return ip_address;
        }

        ISocket::ISocket()
        {
            socket_state = SOCKET_STATE::IDLE;
        }

        IPaddress ISocket::getIPaddress()
        {
            return ip;
        }

        NetPackage ISocket::getPackage()
        {
            return package;
        }

        void ISocket::setPackage(NetPackage package)
        {
            this->package = package;
        }

        SOCKET_STATE ISocket::getSocketState()
        {
            return socket_state;
        }

        bool ISocket::resolve(IPaddress &ip)
        {
            bool success = true;
            const char *host = nullptr;
            this->ip = ip;

            if((host = SDLNet_ResolveIP(&ip)) == nullptr)
            {
                success = false;
                UTIL::Log::err(SDLNet_GetError());
            }
            return success;
        }

        bool ISocket::resolve(const std::string host, Uint16 port)
        {
            if(socket_state < SOCKET_STATE::RESOLVED)
            {
                if(host.empty())
                {
                    if(SDLNet_ResolveHost(&ip, nullptr, port) < 0)
                    {
                        std::string err = "Socket resolve: ";
                        UTIL::Log::err(err + SDLNet_GetError());
                    }
                    else
                    {
                        socket_state = SOCKET_STATE::RESOLVED;
                        return true;
                    }
                }
                else
                {
                    if(SDLNet_ResolveHost(&ip, host.c_str(), port) < 0)
                    {
                        std::string err = "Socket resolve: ";
                        UTIL::Log::err(err + SDLNet_GetError());
                    }
                    else
                    {
                        socket_state = SOCKET_STATE::RESOLVED;
                        return true;
                    }
                }
            }
            return false;
        }

        bool ISocket::isOpen()
        {
            return socket_state >= SOCKET_STATE::OPEN;
        }

        bool ISocket::isResolved()
        {
            return socket_state >= SOCKET_STATE::RESOLVED;
        }
    }
}
