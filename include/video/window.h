#ifndef TURBO_WINDOW_H
#define TURBO_WINDOW_H

#include <SDL_events.h>
#include <SDL_video.h>

#include "video/video_def.h"
#include "math/math.h"

namespace TURBO
{
    namespace VIDEO
    {
        class Window
        {
        private:
            SDL_Window *window;
            MATH::Rect size;
            bool shown          = false;
            bool exposed        = false;
            bool restored       = false;
            bool minimized      = false;
            bool maximized      = false;
            bool mouse_focus    = false;
            bool focus          = false;
            bool closed         = false;

        public:
            Window(const std::string &title, MATH::Rect geometry, Uint32 flags);
            ~Window();
            SDL_Window * getWindow();
            MATH::Rect &getSize();
            void pollEvent(SDL_Event &event);
            bool isShown() const;
            bool isExposed() const;
            bool isRestored() const;
            bool isMinimized() const;
            bool isMaximized() const;
            bool hasMouseFocus() const;
            bool isFocus() const;
            bool isClosed() const;
        };
    }
}

#endif //TURBO_WINDOW_H
