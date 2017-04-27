#include "turbo/application.h"

using TURBO::Application;
using namespace GUI;
using namespace GEOMETRY;
using namespace AUDIO;
using namespace SCRIPT;

int main(int argc, char ** argv)
{
    Application app = Application();

    Window window = Window("Test", Rectangle(50, 50, 500, 300), TURBO::SDL_WINDOW_FLAGS);
    GameRenderer game_renderer = GameRenderer(window, TURBO::SDL_RENDER_FLAGS);
    game_renderer.setDrawColor((Color)TURBO::BLUE);

    Sprite sp(TURBO::TURBO_PATH_XML_IMAGE + "image_test.xml", true);
    Font fo(TURBO::TURBO_PATH_XML_FONT + "font_test.xml", true);
    Chunk ch(TURBO::TURBO_PATH_XML_AUDIO + "sound/chunk_test.xml", true);
    Music mu(TURBO::TURBO_PATH_XML_AUDIO + "music/music_test.xml", true);

    Mix_Volume(-1, 5);
    Mix_VolumeMusic(5);

    //ch.play(0, 0);
    //mu.play(0);

    Widget widget = Widget(Rectangle(0, 0, 125, 75));
    Button button = Button("Click", Rectangle(0, 0, 50, 50));
    widget.setChild(&button);
    widget.setPosition(Point(50, 50));
    widget.setBackgroundColor({0, 100, 100, 255});
    button.setBorderColor({255, 255, 0, 255});

    bool running = true;
    while(running == true)
    {
        SDL_Event event;
        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
            case SDL_QUIT:
                {
                    running = false;
                    break;
                }
            }
            game_renderer.clear();
            widget.draw(game_renderer);
            game_renderer.present();
        }
    }
    return 0;
}