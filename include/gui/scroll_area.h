#ifndef TURBO_SCROLLAREA_H
#define TURBO_SCROLLAREA_H

#include "gui/object.h"

namespace TURBO
{
    namespace GUI
    {
        class ScrollArea
            : public Object
        {
        private:
            MATH::Rect clip_rect   = MATH::Rect();
            bool       v_scrolling = true;
            bool       h_scrolling = true;

        public:
            ScrollArea(Object *parent = nullptr);

            bool getScrolling();

            /**
             * Enables or disables scrolling for both directions.
             * @param scrolling
             * @return true if both directions are enabled
             */
            bool setScrolling(bool scrolling);

            bool getVerticalScrolling();

            /**
             * Enables or disables scrolling for vertical direction.
             * @param scrolling
             * @return true if vertical scrolling is enabled
             */
            bool setVerticalScrolling(bool v_scrolling);

            bool getHorizontalScrolling();

            /**
             * Enables or disables scrolling for horizontal direction.
             * @param scrolling
             * @return true if horizontal scrolling is enabled
             */
            bool setHorizontalScrolling(bool h_scrolling);

            virtual void pollEvent(SDL_Event *event) override;

            virtual void draw(VIDEO::Renderer *renderer) override;
        };
    }
}

#endif //TURBO_SCROLLAREA_H
