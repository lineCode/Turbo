#ifndef TURBO_WINDOW_H
#define TURBO_WINDOW_H

#include <SDL_events.h>
#include <SDL_video.h>

#include "video/video_def.h"
#include "math/math.h"
#include "system/sdl.h"
#include "util/log.h"

namespace TURBO
{
    namespace VIDEO
    {
        class Window
        {
        private:
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
            explicit Window(const std::string &title = "Window Title",
                            MATH::Rect size = MATH::Rect(50, 50, 640, 480),
                            Uint32 flags = SDL_WINDOW_SHOWN);

            ~Window();

            SDL_Window *getWindow();

            MATH::Point getPosition();

            Window &setPosition(MATH::Point pos);

            MATH::Rect getSize();

            Window &setSize(MATH::Rect size);

            MATH::Rect getBorderSize();

            MATH::Rect getMinimumSize();

            Window &setMinimumSize(Sint32 w, Sint32 h);

            MATH::Rect getMaximumSize();

            Window &setMaximumSize(Sint32 w, Sint32 h);

            Uint32 getFlags();

            Window &setFlags(Uint32 flags);

            bool getGrab();

            Window &setGrab(bool grabbed);

            Window &setInputFocus();

            Window &setHitTest(SDL_HitTest callback, void *data);

            Window &show();

            Window &hide();

            Window &setBordered(bool bordered);

            Window &setBrightness(float brightness);

            float getBrightness();

            Window &setOpacity(float opacity);

            float getOpacity();

            Window &setFullScreen(Uint32 flag);

            Window &setGammaRamp(Uint16 r, Uint16 g, Uint16 b);

            Sint32 getID();

            std::string getTitle();

            Window &setIcon(SDL_Surface *icon);

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