#include "turbo/application.h"

using TURBO::Application;
using namespace GUI;
using namespace GEOMETRY;
using namespace AUDIO;
using namespace SCRIPT;

int main(int argc, char ** argv)
{
//    Application app = Application();
//
//    Window window = Window("Test", Rectangle(50, 50, 500, 300), TURBO::SDL_WINDOW_FLAGS);
//    GameRenderer game_renderer = GameRenderer(window, TURBO::SDL_RENDER_FLAGS);
//    game_renderer.setDrawColor(TURBO::BLUE);
//
//    Sprite sp(TURBO::TURBO_PATH_XML_IMAGE + "image_test.xml", true);
//    Font fo(TURBO::TURBO_PATH_XML_FONT + "font_test.xml", true);
//    Chunk ch(TURBO::TURBO_PATH_XML_AUDIO + "sound/chunk_test.xml", true);
//    Music mu(TURBO::TURBO_PATH_XML_AUDIO + "music/music_test.xml", true);
//
//    Mix_Volume(0, 50);
//    Mix_VolumeMusic(50);
//
//    //ch.play(0, 100000);
//    mu.play(1);
//    int result = app.run();
//    return result;

    EXTERN::INIParser p("./data/settings.ini");
    for(auto a : p.getINI().kvp)
    {
        cout << a.first << endl;
        for(auto b : a.second)
        {
            cout << b.first << " = " << b.second << endl;
        }
    }
    return 0;
}