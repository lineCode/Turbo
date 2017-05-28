#include "gui/gui.h"
#include "system/system.h"

using namespace SYSTEM;
using namespace GUI;

int main(int argc, char ** argv)
{
    SDL sdl = SDL();
    string content = "A long String over a line. This is an example -- Or is it?!";
    Window win = Window("test text", GEOMETRY::Rectangle(0, 0, 800, 500));
    IRenderer renderer = IRenderer(win);
    Font font = Font("font.ttf", 50);
    Text text = Text(renderer, font, content, RENDER_MODE::SOLID, Color(255, 255, 255, 255));

    renderer.setResetColor(Color(0, 0, 100, 255));

    renderer.clear();
    text.draw(renderer);
    renderer.present();
    SDL_Delay(3000);

    return 0;
}