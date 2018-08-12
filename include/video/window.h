#ifndef TURBO_WINDOW_H
#define TURBO_WINDOW_H

#include <SDL_events.h>
#include <SDL_video.h>

#include "video/video_def.h"
#include "video/color.h"
#include "math/math.h"
#include "system/sdl.h"
#include "util/log.h"

namespace TURBO
{
    namespace VIDEO
    {
        class IWindow
        {
        protected:
            SDL_Window  *window     = nullptr;
            Uint32      flags       = 0x0;
            MATH::Point position    = MATH::Point();
            MATH::Rect  size        = MATH::Rect();
            std::string title       = "";
            bool        exposed     = false;
            bool        shown       = false;
            bool        minimized   = false;
            bool        maximized   = false;
            bool        restored    = false;
            bool        mouse_focus = false;
            bool        focus       = false;
            bool        closed      = false;

        public:
            IWindow(const std::string &title, MATH::Rect size, Uint32 flags);

            ~IWindow();

            SDL_Window *getWindow();

            MATH::Point getPosition();

            IWindow &setPosition(MATH::Point pos);

            MATH::Rect getSize();

            IWindow &setSize(MATH::Rect size);

            MATH::Rect getBorderSize();

            MATH::Rect getMinimumSize();

            IWindow &setMinimumSize(Sint32 w, Sint32 h);

            MATH::Rect getMaximumSize();

            IWindow &setMaximumSize(Sint32 w, Sint32 h);

            Uint32 getFlags();

            IWindow &setFlags(Uint32 flags);

            bool getGrab();

            IWindow &setGrab(bool grabbed);

            IWindow &setInputFocus();

            IWindow &setHitTest(SDL_HitTest callback, void *data);

            IWindow &show();

            IWindow &hide();

            IWindow &setBordered(bool bordered);

            IWindow &setBrightness(float brightness);

            float getBrightness();

            IWindow &setOpacity(float opacity);

            float getOpacity();

            IWindow &setFullScreen(Uint32 flag);

            IWindow &setGammaRamp(Uint16 r, Uint16 g, Uint16 b);

            Sint32 getID();

            std::string getTitle();

            IWindow &setIcon(SDL_Surface *icon);

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

        class Window
            : public IWindow
        {
        public:
            Window(const std::string &title, MATH::Rect size, Uint32 flags);
        };

        class ShapedWindow
            : public IWindow
        {
        private:
            SDL_Surface         *shape = nullptr;
            SDL_WindowShapeMode mode   = {};

        public:
            ShapedWindow(const std::string &title, MATH::Rect size, SDL_Surface *shape, Uint32 flags);

            SDL_Surface *getShape();

            ShapedWindow &setShape(SDL_Surface *shape, Color color_key = BLACK);
        };
    }
}

#endif //TURBO_WINDOW_H