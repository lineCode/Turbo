#include "gui/gui.h"
#include "Turbo.h"

using namespace GUI;

int main(int argc, char ** argv)
{
    Window win = Window("Display", GEOMETRY::Rectangle(20, 20, 500, 100));
    IRenderer ren = IRenderer(win);
    ren.setResetColor(Color(0,20,0,255));
    Sprite sp = Sprite("image.png", false);

    Color col1 = TURBO::RED;
    Color col2 = {50, 255, 60, 150};

    Texture tex = Texture(ren, sp);

    ren.clear();
    //ren.draw(tex);
    tex.
    ren.present();
    SDL_Delay(2000);
    ren.clear();
    ren.drawLine(GEOMETRY::Line(20, 20, 100, 50), col1);
    ren.present();
    SDL_Delay(2000);
    ren.clear();
    ren.drawLine(GEOMETRY::Line(20, 20, 200, 80), col2);
    ren.present();
    SDL_Delay(2000);
    return 0;
}
