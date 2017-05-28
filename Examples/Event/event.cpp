#include "gui/gui.h"
#include "system/system.h"

using namespace GUI;
using namespace GEOMETRY;

class Dot : public EVENT::IEventListener
{
private:
    Point pos;
    int speed;
public:
    Dot(int speed) : pos(0, 0), speed(speed)
    {
        this->registerEvent(SDL_KEYDOWN, SDLK_w, std::bind(&Dot::up, this));
        this->registerEvent(SDL_KEYDOWN, SDLK_s, std::bind(&Dot::down, this));
        this->registerEvent(SDL_KEYDOWN, SDLK_d, std::bind(&Dot::right, this));
        this->registerEvent(SDL_KEYDOWN, SDLK_a, std::bind(&Dot::left, this));
    };
    void up(){this->pos = this->pos + Point(0, -speed);};
    void down(){this->pos = this->pos + Point(0, speed);};
    void right(){this->pos = this->pos + Point(speed, 0);};
    void left(){this->pos = this->pos + Point(-speed, 0);};
    void draw(IRenderer & renderer){renderer.drawPoint(pos, Color(200, 50, 50, 255));};
};

int main(int argc, char ** argv)
{
    Window win = Window("test event", GEOMETRY::Rectangle(0, 0, 800, 500));
    IRenderer renderer = IRenderer(win);
    renderer.setResetColor(Color(0, 0, 100, 255));
    Dot dot = Dot(5);

    Uint32 time = SDL_GetTicks();
    SDL_Event event;
    Uint32 diff = 0;
    while(diff <= 10000)
    {
        while(SDL_PollEvent(&event))
        {
            EVENT::IEventListener::callEvent(event.type, event.key.keysym.sym);
        }
        renderer.clear();
        dot.draw(renderer);
        renderer.present();
        diff = SDL_GetTicks() - time;
    }

    return 0;
}