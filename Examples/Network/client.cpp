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

    TCPClient   client  = TCPClient("localhost", 13370);
    NetPackage  package;
    NetPackage  temp;
    bool        running = true;
    int         counter = 0;

    client.open();
    cout << "open" << endl;
    while(running == true)
    {
		cout << "pull" << endl;
        if(client.receive(package))
        {
            cout << "got package" << endl;
        }
        SDL_Delay(1000);
        counter++;
        if(counter > 3)
        {
            break;
        }
    }
    cout << "Stop connection" << endl;

    SDLNet_Quit();
    SDL_Quit();
    return 0;
}
