#include "video/window.h"

namespace TURBO
{
    namespace VIDEO
    {
        Window::Window(const std::string &title, MATH::Rect size, Uint32 flags)
            : flags(flags),
              title(title),
              position(size.topLeft()),
              size(size)
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

        Window::~Window()
        {
            if(window != nullptr)
            {
                SDL_DestroyWindow(window);
            }
        }

        SDL_Window * Window::getWindow()
        {
            return window;
        }

        MATH::Point Window::getPosition()
        {
            MATH::Point p;
            SDL_GetWindowPosition(window, &p.x, &p.y);
            return p;
        }

        Window &Window::setPosition(MATH::Point pos)
        {
            position = pos;
            SDL_SetWindowPosition(window, pos.x, pos.y);
            return *this;
        }

        MATH::Rect Window::getSize()
        {
            MATH::Rect r;
            SDL_GetWindowSize(window, &r.w, &r.h);
            return r;
        }

        Window &Window::setSize(MATH::Rect size)
        {
            size = MATH::Rect(position.x, position.y, size.w, size.h);
            SDL_SetWindowSize(window, size.w, size.h);
            return *this;
        }

        MATH::Rect Window::getBorderSize()
        {
            MATH::Rect borders;
            SDL_GetWindowBordersSize(window, &borders.x, &borders.y, &borders.w, &borders.h);
            return borders;
        }

        MATH::Rect Window::getMinimumSize()
        {
            MATH::Rect r;
            SDL_GetWindowMinimumSize(window, &r.w, &r.h);
            return r;
        }

        Window &Window::setMinimumSize(Sint32 w, Sint32 h)
        {
            SDL_SetWindowMinimumSize(window, w, h);
            return *this;
        }

        MATH::Rect Window::getMaximumSize()
        {
            MATH::Rect r;
            SDL_GetWindowMaximumSize(window, &r.w, &r.h);
            return r;
        }

        Window &Window::setMaximumSize(Sint32 w, Sint32 h)
        {
            SDL_SetWindowMaximumSize(window, w, h);
            return *this;
        }

        Window &Window::setFlags(Uint32 flags)
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

        Uint32 Window::getFlags()
        {
            return flags;
        }

        bool Window::getGrab()
        {
            return SDL_GetWindowGrab(window);
        }

        Window &Window::setGrab(bool grabbed)
        {
            SDL_SetWindowGrab(window, static_cast<SDL_bool>(grabbed));
            return *this;
        }

        Window &Window::setInputFocus()
        {
            SDL_SetWindowInputFocus(window);
            return *this;
        }

        Window &Window::setHitTest(SDL_HitTest callback, void *data)
        {
            SDL_SetWindowHitTest(window, callback, data);
            return *this;
        }

        Window &Window::show()
        {
            SDL_ShowWindow(window);
            return *this;
        }

        Window &Window::hide()
        {
            SDL_HideWindow(window);
            return *this;
        }

        Window &Window::setBordered(bool bordered)
        {
            SDL_SetWindowBordered(window, static_cast<SDL_bool>(bordered));
            return *this;
        }

        Window &Window::setBrightness(float brightness)
        {
            SDL_SetWindowBrightness(window, brightness);
            return *this;
        }

        float Window::getBrightness()
        {
            return SDL_GetWindowBrightness(window);
        }

        Window &Window::setOpacity(float opacity)
        {
            SDL_SetWindowOpacity(window, opacity);
            return *this;
        }

        float Window::getOpacity()
        {
            float opacity;
            SDL_GetWindowOpacity(window, &opacity);
            return opacity;
        }

        Window &Window::setFullScreen(Uint32 flag)
        {
            SDL_SetWindowFullscreen(window, flag);
            return *this;
        }

        Window &Window::setGammaRamp(Uint16 r, Uint16 g, Uint16 b)
        {

        }

        Sint32 Window::getID()
        {
            return 0;
        }

        std::string Window::getTitle()
        {
            return std::__cxx11::string();
        }

        Window &Window::setIcon(SDL_Surface *icon)
        {

        }

        void Window::pollEvent(SDL_Event &event)
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
                restored = false;
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

        bool Window::isShown() const
        {
            return shown;
        }

        bool Window::isExposed() const
        {
            return exposed;
        }

        bool Window::isRestored() const
        {
            return restored;
        }

        bool Window::isMinimized() const
        {
            return minimized;
        }

        bool Window::isMaximized() const
        {
            return maximized;
        }

        bool Window::hasMouseFocus() const
        {
            return mouse_focus;
        }

        bool Window::isFocus() const
        {
            return focus;
        }

        bool Window::isClosed() const
        {
            return closed;
        }
    }
}