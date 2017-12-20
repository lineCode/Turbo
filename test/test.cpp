#include "turbo.h"

namespace TA = TURBO::AUDIO;
namespace TV = TURBO::VIDEO;
namespace TU = TURBO::UTIL;
namespace TM = TURBO::MATH;
namespace TS = TURBO::SYSTEM;

int main(int argc, char ** argv)
{
    TS::PTimer ptimer{};

    TS::SDL sdl = TS::SDL(SDL_INIT_EVERYTHING);
    sdl.initIMG(IMG_INIT_PNG);
    sdl.initMIX(MIX_INIT_MP3 | MIX_INIT_FLAC);

    auto window = TV::Window("Title", TM::Rect(50, 50, 500, 500), SDL_WINDOW_SHOWN);
    auto renderer = TV::Renderer(window, -1, SDL_RENDERER_ACCELERATED);
    auto main_widget = TURBO::GUI::MainWidget(window, renderer);
    auto vbox = TURBO::GUI::Box(&main_widget);
    auto b1 = TURBO::GUI::Button("Hi");
    auto b2 = TURBO::GUI::Button("Bye");

    b1.setBackground(TURBO::GUI::Background({255, 255, 0, 255}));
    b2.setBackground(TURBO::GUI::Background({255, 0, 0, 255}));
    vbox.addWidget(&b1);
    vbox.addWidget(&b2);

    if(TS::SDL::SDL_IS_INIT && TS::SDL::MIX_IS_INIT)
    {
        std::cout << "init" << std::endl;
    }

    auto mp = TA::MediaPlayer("resources/audio/");
    auto c = TA::Chunk("resources/audio/piano.wav");

    Mix_VolumeChunk(c.getChunk(), 128);
    Mix_VolumeMusic(128);

    c.play(2000);

    bool running = true;
    while(running)
    {
        SDL_Event event;
        while(SDL_PollEvent(&event))
        {
            if(event.type == SDL_KEYDOWN)
            {
                if(event.key.keysym.sym == SDLK_ESCAPE)
                {
                    mp.stop();
                    running = false;
                }
                if(event.key.keysym.sym == SDLK_SPACE)
                {
                    if(mp.getState() == TA::MEDIUM_STATE::STOPPED)
                    {
                        mp.play();
                    }
                    else if(mp.getState() == TA::MEDIUM_STATE::PLAYING)
                    {
                        mp.pause();
                    }
                    else if(mp.getState() == TA::MEDIUM_STATE::PAUSED)
                    {
                        mp.resume();
                    }
                }
            }

            renderer.clear();
            renderer.drawObject(&main_widget);
            renderer.present();
        }
        SDL_Delay(5);
    }

    std::cout << TS::Time::getPTicksToString(ptimer.getTime(), "%Ss %fms %uus %nns") << std::endl;

    return 0;
}