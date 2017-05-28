#include "gui/gui.h"
#include "Turbo.h"

using namespace GUI;

int main(int argc, char ** argv)
{
    Window win = Window("Display", GEOMETRY::Rectangle(20, 20, 500, 300));
    IRenderer ren = IRenderer(win);
    ren.setDrawColor(Color(0,0,0,0));
    Sprite sp = Sprite("Turbo.png", false);

    Texture tex = Texture(ren, sp);
    tex.draw(ren);
    ren.present();
    SDL_Delay(3000);

    return 0;
}
