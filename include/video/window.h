#ifndef TURBO_WINDOW_H
#define TURBO_WINDOW_H

#include <SDL2pp/SDL2pp.hh>

#include "video/opengl.h"
#include "math/math.h"

namespace TURBO
{
    namespace VIDEO
    {
        class Window : public SDL2pp::Window
        {
        private:
            SDL_GLContext context;
            MATH::Rect geometry;
            bool shown = false;
            bool exposed = false;
            bool restored = false;
            bool minimized = false;
            bool maximized = false;
            bool mouse_focus = false;
            bool focus = false;
            bool closed = false;

        public:
            Window(const std::string &title, MATH::Rect geometry, Uint32 flags);
            ~Window() override;
            MATH::Rect getGeometry();
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
