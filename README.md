# Turbo

- C++ Class Wrapper for SDL2
- 2D Framework for games 


# Examples

``` cpp
#include "turbo.h"

namespace TA = TURBO::AUDIO;
namespace TG = TURBO::GUI;
namespace TV = TURBO::VIDEO;
namespace TU = TURBO::UTIL;
namespace TM = TURBO::MATH;
namespace TS = TURBO::SYSTEM;

void over()
{
    std::cout << "hover" << std::endl;
}


void out()
{
    std::cout << "out" << std::endl;
}


int main(int argc, char ** argv)
{
    TS::PTimer ptimer{};

    LOG("Loading libraries");

    TS::SDL sdl = TS::SDL(SDL_INIT_EVERYTHING);
    sdl.initIMG(IMG_INIT_PNG);
    sdl.initMIX(MIX_INIT_MP3 | MIX_INIT_FLAC);
    sdl.initTTF();

    LOG("Set up UI");

    auto window = TV::Window("Title", TM::Rect(50, 50, 600, 600), SDL_WINDOW_SHOWN);
    auto renderer = TV::Renderer(window, -1, SDL_RENDERER_ACCELERATED);
    auto main_widget = TURBO::GUI::MainWidget(window, renderer);
    auto hbox = TURBO::GUI::Box(&main_widget, TURBO::GUI::ORIENTATION::VERTICAL);
    auto vbox1 = TURBO::GUI::Box(nullptr, TURBO::GUI::ORIENTATION::HORIZONTAL);
    auto vbox2 = TURBO::GUI::Box(nullptr, TURBO::GUI::ORIENTATION::HORIZONTAL);
    auto b1 = TURBO::GUI::Button("Hi");
    auto b2 = TURBO::GUI::Button("Bye");
    auto b3 = TURBO::GUI::Button("Today");
    auto b4 = TURBO::GUI::Button("Asd\nss\nsda");
    auto b5 = TURBO::GUI::Button("Test");

    b1.setBackground(TURBO::GUI::Background({255, 255, 0, 255}));
    b2.setBackground(TURBO::GUI::Background({255, 0, 0, 255}));
    b3.setBackground(TURBO::GUI::Background({255, 0, 255, 255}));
    b4.setBackground(TURBO::GUI::Background({0, 0, 0, 255}));
    b5.setBackground(TURBO::GUI::Background({0, 255, 255, 255}));
    hbox.addWidget(&vbox1);
    hbox.addWidget(&b5);
    hbox.addWidget(&vbox2);
    vbox1.addWidget(&b1);
    vbox1.addWidget(&b2);
    vbox2.addWidget(&b3);
    vbox2.addWidget(&b4);

    b1.registerCallback(TG::EVENT_TYPE::ON_MOUSE_OVER, over);
    b1.registerCallback(TG::EVENT_TYPE::ON_MOUSE_OUT, out);

    LOG("Start application");

    while(TS::SYSTEM_RUNNING)
    {
        SDL_Event event = {};
        while(SDL_PollEvent(&event))
        {
            TURBO::INPUT::Mouse::pollEvent(event);
            b1.pollEvent(event);
            if(event.type == SDL_KEYDOWN)
            {
                TS::SYSTEM_RUNNING = false;
            }
            renderer.clear();
            main_widget.draw(&renderer);
            renderer.present();
        }
        SDL_Delay(5);
    }

    LOG("Stop application");

    std::cout << TS::Time::getPTicksToString(ptimer.getTime(), "%s %fms %uus %nns") << std::endl;
    return 0;
}

```

# Development

##SDL

- [SDL 2](https://www.libsdl.org/download-2.0.php)
- [IMG 2](https://www.libsdl.org/projects/SDL_image/)
- [TTF 2](https://www.libsdl.org/projects/SDL_ttf/)
- [MIX 2](https://www.libsdl.org/projects/SDL_mixer/)
- [NET 2](https://www.libsdl.org/projects/SDL_net/)

### Linux

- most linux distributions will have sdl as supported package (libsdl2-dev)

### Windows

Download the development files for your platform and your Environment. You may want to download the binary files as well.
- **If you have trouble with 64 bit files may have to use the 32 bit libraries in order to compile for 64 bit systems.**

Extract the include and lib directory you have to use to your libraries path (example: `C:/libraries/SDL/include/`).
- **Remember this path, you will need this later to configure the make file.**

## Python

### Linux

Most linux distributions will have python as supported package (python-dev). 
If you decide otherwise you have to download the following archive.

- [Python 34](https://www.python.org/downloads/release/python-346/)

Download the tarball/zip and extract it to your desired path.
***Remember the path of the include/ and libs/ directories***

### Windows

- [Python 34](https://www.python.org/downloads/release/python-346/)

Download the tarball/zip and extract it to your desired path.
***Remember the path of the include/ and libs/ directories***


# Installation

## Generating Executables

###Visual Studio

-

###GNU make

1. Change parameters at the section `# Define Variables` in the file Turbo/Turbo.make to fit your system requirements:

	1.1 `INCD`: include directory of SDL2 and Python
	
	[example `INCD := -IC:/libraries/SDL/include/ -IC:/libraries/Python/include/`]
	
	1.2 `LIBD`: library directory of SDL2 and Python
	
	[example: `LIBD := -IC:/libraries/SDL/lib/ -IC:/libraries/Python/libs/`]
	
	1.3 `PROJECT`: desired output file name

	[example: `PROJECT := MyApp`]

	1.4 `CFLAGS` and `CPPFLAGS`: compiler flags
	
	[example: `CFLAGS := -c -Wall -Werror` and `CPPFLAGS := -std=c++11`]
	
	1.5 `LDFLAGS`: linker flags

	[example: `LDFLAGS := -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer`]

If you have done all the above things you can now build Turbo with the following command.
(This requires, that you have added the make executable to your Environment path)
	
	`make Turbo.make`

This command should generate object files into the directory obj and a executable in the base directory of the project.

###cmake

-

###qmake

The easiest way (IMO) is to use qmake.

- Get a functioning version of qmake (comes with QT, but is available as standalone)
- create a .pro file
    - execute `qmake -project` in the working directory
- execute `qmake`
- execute `make`
- an executable should be generated in the working directory

For more information and help take a look at either 'Visual Studio Support' or 'GNU make'.
