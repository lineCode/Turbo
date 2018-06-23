#include "turbo.h"

namespace TA = TURBO::AUDIO;
namespace TG = TURBO::GUI;
namespace TCH = TURBO::CHART;
namespace TV = TURBO::VIDEO;
namespace TI = TURBO::INPUT;
namespace TU = TURBO::UTIL;
namespace TM = TURBO::MATH;
namespace TN = TURBO::NET;
namespace TS = TURBO::SYSTEM;
namespace TC = TURBO::SCRIPT;

void server()
{
    TS::SDL sdl = TS::SDL();
    sdl.initSDL(SDL_INIT_EVERYTHING);
    sdl.initNET();


    LOG("START SERVER");

    TN::TCPServer  server = TN::TCPServer(13370);
    TN::NetPackage package{};

    Uint16 text[] = {0x050a, 0x0065, 0x006c, 0x006c,
                     0x006f, 0x0020, 0x02ac, 0x006f,
                     0x0072, 0x006c, 0x0064, 0x0020,
                     0x0074, 0x006f, 0x0020, 0x03a8,
                     0x006f, 0x0075, 0x0020, 0x006d,
                     0x0079, 0x0020, 0x0066, 0x0072,
                     0x0069, 0x20ac, 0x006e, 0x0064,
                     0x002e, 0x0020, 0xfc00, 0x0020,
                     0x0904, 0x0020, 0x10F7, 0x1435};

    std::copy(text, text + sizeof(text) / sizeof(Uint16), package.data);

    // Wait for 1 Client, wait at max 10 sec
    server.waitAccept(1, 10000);

    server.send(package);

    while(!server.receive(package))
    {
        SDL_Delay(200);
    }

    package.print();
}

void client()
{
    TS::SDL sdl = TS::SDL();
    sdl.initSDL(SDL_INIT_EVERYTHING);
    sdl.initNET();


    TN::TCPClient  client = TN::TCPClient("127.0.0.1", 13370);
    TN::NetPackage package{};

    while(!client.receive(package))
    {
        SDL_Delay(200);
    }

    package.print();

    package.data[TN::PACKAGE_BUFFER] = {0};
    Uint16 text[] = {0x050A, 0x0065, 0x006C, 0x006C,
                     0x006F, 0x0020, 0x15F7, 0x0020,
                     0x15C6, 0x0020, 0x18B7, 0x0020,
                     0x1729};


    std::copy(text, text + sizeof(text) / sizeof(Uint16), package.data);

    client.send(package);
}