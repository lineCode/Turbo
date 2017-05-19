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

    TCPServer   server  = TCPServer(13370);
    TCPClient   client  = TCPClient();
    NetPackage  package;
    NetPackage  temp;
    bool        running = true;

    server.open();
    cout << "open" << endl;
    while(!server.accept(client))
    {
        SDL_Delay(1000);
    }
    cout << "Client connected" << endl;

    while(client.send(package))
    {
        cout << "push" << endl;
        SDL_Delay(1000);
    }
    cout << "Client disconnected" << endl;

    SDLNet_Quit();
    SDL_Quit();
    return 0;
}
