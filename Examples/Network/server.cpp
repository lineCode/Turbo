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

    NetPackage * package;
    package->data[0] = 0xFFAA;
    package->data[1] = 0xAADD;

    TCPClient server = TCPClient("", 13370);
    TCPClient client = TCPClient();
    server.open();
    cout << "Server open" << endl;
    while(client.getSocket() == NULL)
    {
        server.accept(client);
        SDL_Delay(1000);
    }
    cout << "Server has a client" << endl;

    while(1)
    {/*
        if(client.receive(*package))
        {
            cout << "Message received: " << endl;
            for(Uint16 date : package->data)
            {
                cout << std::hex << date << " ";
            }
            cout << endl;
        }*/
        client.send(*package);
        SDL_Delay(1000);
    }

    client.close();
    server.close();

    SDLNet_Quit();
    SDL_Quit();
    return 0;
}