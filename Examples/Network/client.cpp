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
    bool running = true;
    int counter = 0;
    TCPClient client = TCPClient("localhost", 1337);

    client.open();
    cout << "Client open" << endl;
    while(running == true)
    {
        if(client.receive(package))
        {
            cout << "Message received: " << endl;
            for(Uint16 date : package.data)
            {
                cout << std::hex << date << " ";
            }
            cout << endl;
        }
        SDL_Delay(1000);
        counter++;
        if(counter == 3)
        {
            package.data[0] = 0x0000;
            client.send(package);
        }
    }

    client.close();

    SDLNet_Quit();
    SDL_Quit();
    return 0;
}
