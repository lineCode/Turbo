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

    TCPServer server = TCPServer(1337);
    TCPClient client = TCPClient();
    NetPackage package;
    bool running = true;

    server.open();
    cout << "Server open" << endl;
    while(client.getSocket() == NULL)
    {
        server.accept(client);
        SDL_Delay(1000);
    }
    cout << "Server has a client" << endl;


    while(running == true)
    {
        for(int i = 0; i < TURBO::SDL_NET_BUFFER_LENGTH; ++i)
            package.data[i] = rand() % 0xFFFF;

/*
        if(client.receive(package))
        {
            if(package.data[0] == 0x0000)
                running = false;
            cout << "Message received: " << endl;
            for(Uint16 date : package.data)
            {
                cout << std::hex << date << " ";
            }
            cout << endl;
        }
        if(server.receive(package))
        {
            if(package.data[0] == 0x0000)
                running = false;
            cout << "Message received: " << endl;
            for(Uint16 date : package.data)
            {
                cout << std::hex << date << " ";
            }
            cout << endl;
        }*/
        client.send(package);
        SDL_Delay(1000);
    }

    client.close();
    server.close();

    SDLNet_Quit();
    SDL_Quit();
    return 0;
}
