#include "gui/gui_widget.h"

using namespace GEOMETRY;
using namespace GUI;

int main(int argc, char ** argv)
{
    Window win = Window("Widget-Test", Rectangle(10, 10, 500, 300));
    IRenderer ren = IRenderer(win);
    Widget widget1 = Widget("widget.xml");
    Widget widget2 = Widget(Rectangle(5, 5, 200, 100));

    widget2.setBackgroundColor(Color(200, 100, 50, 100));
    widget2.setBorderColor(Color(10, 100, 255, 255));

    ren.clear();

    widget1.draw(ren);
    widget2.draw(ren);

    ren.present();

    SDL_Delay(3000);

    return 0;
}