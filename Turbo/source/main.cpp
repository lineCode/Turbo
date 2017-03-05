#include "turbo/application.h"

using TURBO::Application;
using namespace GUI;
using namespace GEOMETRY;
using namespace AUDIO;

int main(int argc, char ** argv)
{
    Application app = Application();

    Window window = Window("Test", Rectangle(50, 50, 500, 300), TURBO::SDL_WINDOW_FLAGS);
    GameRenderer game_renderer = GameRenderer(window, TURBO::SDL_RENDER_FLAGS);
    game_renderer.setDrawColor(TURBO::BLUE);

//    int i = 0;
//    while(i < 100)
//    {
//        cout << i << endl;
//        game_renderer.clear();
//
//        game_renderer.present();
//        SDL_Delay(200);
//        i++;
//    }
    Sprite sp(TURBO::TURBO_PATH_XML_IMAGE + "image_test.xml", true);
    Font fo(TURBO::TURBO_PATH_XML_FONT + "font_test.xml", true);
    Chunk ch(TURBO::TURBO_PATH_XML_AUDIO + "sound/sound_test.xml", true);
    //Music mu(TURBO::TURBO_PATH_XML_AUDIO + "music/music_test.xml", true);

    //ch.play(0, 1000);
    SDL_Delay(200);
    //mu.play(0);
    int result = app.run();
    return result;
}