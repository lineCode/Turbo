#include <SDL_shape.h>
#include "video/window.h"

namespace TURBO
{
    namespace VIDEO
    {
        IWindow::IWindow(const std::string &title, MATH::Rect size, Uint32 flags)
            : title(title),
              size(size),
              flags(flags)
        {

        }

        IWindow::~IWindow()
        {
            if(window != nullptr)
            {
                SDL_DestroyWindow(window);
            }
        }

        SDL_Window *IWindow::getWindow()
        {
            return window;
        }

        MATH::Point IWindow::getPosition()
        {
            MATH::Point p;
            SDL_GetWindowPosition(window, &p.x, &p.y);
            return p;
        }

        IWindow &IWindow::setPosition(MATH::Point pos)
        {
            position = pos;
            SDL_SetWindowPosition(window, pos.x, pos.y);
            return *this;
        }

        MATH::Rect IWindow::getSize()
        {
            MATH::Rect r;
            SDL_GetWindowSize(window, &r.w, &r.h);
            return r;
        }

        IWindow &IWindow::setSize(MATH::Rect size)
        {
            size = MATH::Rect(position.x, position.y, size.w, size.h);
            SDL_SetWindowSize(window, size.w, size.h);
            return *this;
        }

        MATH::Rect IWindow::getBorderSize()
        {
            MATH::Rect borders;
            SDL_GetWindowBordersSize(window, &borders.x, &borders.y, &borders.w, &borders.h);
            return borders;
        }

        MATH::Rect IWindow::getMinimumSize()
        {
            MATH::Rect r;
            SDL_GetWindowMinimumSize(window, &r.w, &r.h);
            return r;
        }

        IWindow &IWindow::setMinimumSize(Sint32 w, Sint32 h)
        {
            SDL_SetWindowMinimumSize(window, w, h);
            return *this;
        }

        MATH::Rect IWindow::getMaximumSize()
        {
            MATH::Rect r;
            SDL_GetWindowMaximumSize(window, &r.w, &r.h);
            return r;
        }

        IWindow &IWindow::setMaximumSize(Sint32 w, Sint32 h)
        {
            SDL_SetWindowMaximumSize(window, w, h);
            return *this;
        }

        IWindow &IWindow::setFlags(Uint32 flags)
        {
            this->flags = flags;

            if(this->flags != flags)
            {
                if(SYSTEM::SDL::SDL_IS_INIT)
                {
                    if(window != nullptr)
                    {
                        SDL_DestroyWindow(window);
                    }
                    window = SDL_CreateWindow(title.c_str(), position.x, position.y, size.w, size.h, flags);
                }
            }
            return *this;
        }

        Uint32 IWindow::getFlags()
        {
            return flags;
        }

        bool IWindow::getGrab()
        {
            return SDL_GetWindowGrab(window);
        }

        IWindow &IWindow::setGrab(bool grabbed)
        {
            SDL_SetWindowGrab(window, static_cast<SDL_bool>(grabbed));
            return *this;
        }

        IWindow &IWindow::setInputFocus()
        {
            SDL_SetWindowInputFocus(window);
            return *this;
        }

        IWindow &IWindow::setHitTest(SDL_HitTest callback, void *data)
        {
            SDL_SetWindowHitTest(window, callback, data);
            return *this;
        }

        IWindow &IWindow::show()
        {
            SDL_ShowWindow(window);
            return *this;
        }

        IWindow &IWindow::hide()
        {
            SDL_HideWindow(window);
            return *this;
        }

        IWindow &IWindow::setBordered(bool bordered)
        {
            SDL_SetWindowBordered(window, static_cast<SDL_bool>(bordered));
            return *this;
        }

        IWindow &IWindow::setBrightness(float brightness)
        {
            SDL_SetWindowBrightness(window, brightness);
            return *this;
        }

        float IWindow::getBrightness()
        {
            return SDL_GetWindowBrightness(window);
        }

        IWindow &IWindow::setOpacity(float opacity)
        {
            SDL_SetWindowOpacity(window, opacity);
            return *this;
        }

        float IWindow::getOpacity()
        {
            float opacity;
            SDL_GetWindowOpacity(window, &opacity);
            return opacity;
        }

        IWindow &IWindow::setFullScreen(Uint32 flag)
        {
            SDL_SetWindowFullscreen(window, flag);
            return *this;
        }

        IWindow &IWindow::setGammaRamp(Uint16 r, Uint16 g, Uint16 b)
        {

        }

        Sint32 IWindow::getID()
        {
            return 0;
        }

        std::string IWindow::getTitle()
        {
            return std::__cxx11::string();
        }

        IWindow &IWindow::setIcon(SDL_Surface *icon)
        {

        }

        void IWindow::pollEvent(SDL_Event &event)
        {
            exposed = false;

            if(event.type == SDL_WINDOWEVENT_SHOWN)
            {
                shown = true;
            }
            else if(event.type == SDL_WINDOWEVENT_HIDDEN)
            {
                shown = false;
            }
            else if(event.type == SDL_WINDOWEVENT_EXPOSED)
            {
                exposed = true;
            }
            else if(event.type == SDL_WINDOWEVENT_MINIMIZED)
            {
                minimized = true;
                maximized = false;
                restored  = false;
            }
            else if(event.type == SDL_WINDOWEVENT_MAXIMIZED)
            {
                maximized = true;
                minimized = false;
            }
            else if(event.type == SDL_WINDOWEVENT_RESTORED)
            {
                restored = true;
            }
            else if(event.type == SDL_WINDOWEVENT_ENTER)
            {
                mouse_focus = true;
            }
            else if(event.type == SDL_WINDOWEVENT_LEAVE)
            {
                mouse_focus = false;
            }
            else if(event.type == SDL_WINDOWEVENT_FOCUS_GAINED)
            {
                focus = true;
            }
            else if(event.type == SDL_WINDOWEVENT_FOCUS_LOST)
            {
                focus = false;
            }
            else if(event.type == SDL_WINDOWEVENT_CLOSE)
            {
                closed = true;
            }
            else if(event.type == SDL_WINDOWEVENT_MOVED)
            {

            }
            else if(event.type == SDL_WINDOWEVENT_RESIZED)
            {

            }
            else if(event.type == SDL_WINDOWEVENT_SIZE_CHANGED)
            {

            }
        }

        bool IWindow::isShown() const
        {
            return shown;
        }

        bool IWindow::isExposed() const
        {
            return exposed;
        }

        bool IWindow::isRestored() const
        {
            return restored;
        }

        bool IWindow::isMinimized() const
        {
            return minimized;
        }

        bool IWindow::isMaximized() const
        {
            return maximized;
        }

        bool IWindow::hasMouseFocus() const
        {
            return mouse_focus;
        }

        bool IWindow::isFocus() const
        {
            return focus;
        }

        bool IWindow::isClosed() const
        {
            return closed;
        }

        Window::Window(const std::string &title, MATH::Rect size, Uint32 flags)
            : IWindow(title, size, flags)
        {
            if(SYSTEM::SDL::SDL_IS_INIT)
            {
                window = SDL_CreateWindow(title.c_str(), size.x, size.y, size.w, size.h, flags);

                if(window != nullptr)
                {
                    if(flags & SDL_WINDOW_OPENGL)
                    {
                        SYSTEM::SDL::OPENGL_IS_INIT = true;
                    }
                }
                else
                {
                    UTIL::Log::err(SDL_GetError());
                }
            }
            else
            {
                UTIL::Log::err("SDL is not initialized");
            }
        }


        ShapedWindow::ShapedWindow(const std::string &title, MATH::Rect size, SDL_Surface *shape, Uint32 flags)
            : IWindow(title, size, flags),
              shape(shape)
        {
            if(SYSTEM::SDL::SDL_IS_INIT)
            {
                if(shape != nullptr)
                {
                    window = SDL_CreateShapedWindow(title.c_str(), size.x, size.y, size.w, size.h, flags);
                    SDL_SetWindowPosition(window, size.x, size.y);
                    SDL_SetWindowSize(window, shape->w, shape->h);

                    if(window == nullptr)
                    {
                        UTIL::Log::err(SDL_GetError());
                    }
                }
            }
            else
            {
                UTIL::Log::err("SDL is not initialized");
            }
        }

        SDL_Surface *VIDEO::ShapedWindow::getShape()
        {
            return shape;
        }

        VIDEO::ShapedWindow &VIDEO::ShapedWindow::setShape(SDL_Surface *shape, Color color_key)
        {
            if(SDL_GetRenderer(window) != nullptr)
            {
                if(SDL_ISPIXELFORMAT_ALPHA(shape->format->format))
                {
                    mode.mode                          = ShapeModeBinarizeAlpha;
                    mode.parameters.binarizationCutoff = 0xFF;
                }
                else
                {
                    mode.mode                = ShapeModeColorKey;
                    mode.parameters.colorKey = {
                        color_key.r,
                        color_key.g,
                        color_key.b,
                        color_key.a
                    };
                }
                SDL_SetWindowShape(window, shape, &mode);
            }
            else
            {
                UTIL::Log::err("Shape can only set after the renderer is connected with the window.");
            }
            return *this;
        }
    }
}