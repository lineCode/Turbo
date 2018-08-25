#include "gui/scroll_area.h"

TURBO::GUI::ScrollArea::ScrollArea(TURBO::GUI::Object *parent)
    : Object(parent), clip_rect(0, 0, content.w, content.h)
{

}

bool TURBO::GUI::ScrollArea::getScrolling()
{
    return (v_scrolling && h_scrolling);
}

bool TURBO::GUI::ScrollArea::setScrolling(bool scrolling)
{
    return (setVerticalScrolling(scrolling) && setHorizontalScrolling(scrolling));
}

bool TURBO::GUI::ScrollArea::getVerticalScrolling()
{
    return v_scrolling;
}

bool TURBO::GUI::ScrollArea::setVerticalScrolling(bool v_scrolling)
{
    this->v_scrolling = v_scrolling;
    return this->v_scrolling;
}

bool TURBO::GUI::ScrollArea::getHorizontalScrolling()
{
    return h_scrolling;
}

bool TURBO::GUI::ScrollArea::setHorizontalScrolling(bool h_scrolling)
{
    this->h_scrolling = h_scrolling;
    return this->h_scrolling;
}

void TURBO::GUI::ScrollArea::pollEvent(SDL_Event *event)
{
    Object::pollEvent(event);
    if(wheel_moving)
    {
        if(v_scrolling)
        {
            if(event->wheel.y > 0 && !INPUT::Keyboard::down(SDLK_LSHIFT))
            {
                clip_rect.add(0, -1, 0, 0);
            }
            else if(event->wheel.y < 0 && !INPUT::Keyboard::down(SDLK_LSHIFT))
            {
                clip_rect.add(0, 1, 0, 0);
            }
        }

        if(h_scrolling)
        {
            if(event->wheel.x > 0 || (event->wheel.y > 0 && INPUT::Keyboard::down(SDLK_LSHIFT)))
            {
                clip_rect.add(-1, 0, 0, 0);
            }
            else if(event->wheel.x < 0 || (event->wheel.y < 0 && INPUT::Keyboard::down(SDLK_LSHIFT)))
            {
                clip_rect.add(1, 0, 0, 0);
            }
        }
    }
}

void TURBO::GUI::ScrollArea::draw(TURBO::VIDEO::Renderer *renderer)
{
    //Object::draw(renderer);
    if(v_scrolling)
    {
        // draw vertical scroll bar
    }
    if(h_scrolling)
    {
        // draw horizontal scroll bar
    }
    if(child != nullptr)
    {
        child->draw(renderer);
    }
}
