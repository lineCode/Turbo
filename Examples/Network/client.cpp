#include "net/net.h"

using namespace NET;

int main(int argc, char ** argv)
{
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        SDL_Quit();
        return -1;
    }
    if(SDLNet_Init() < 0)
    {
        return -1;
    }

    NetPackage package;
    TCPClient client = TCPClient("localhost", 13370);

    client.open();
    cout << "Client open" << endl;
    while(1)
    {
        if(client.receive(package))
        {
            cout << "Message received: " << endl;
            for(Uint16 date : package.data)
            {
                cout << std::hex << date << " ";
            }
            cout << endl;
            client.send(package);
        }
        SDL_Delay(1000);
    }

    client.close();

    SDLNet_Quit();
    SDL_Quit();
    return 0;
}