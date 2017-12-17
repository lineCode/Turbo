#include "video/window.h"

namespace TURBO
{
    namespace VIDEO
    {
        Window::Window(const std::string &title, MATH::Rect size, Uint32 flags)
            : size(size)
        {
            window = SDL_CreateWindow(title.c_str(), size.x, size.y, size.w, size.h, flags);
        }

        Window::~Window()
        {
            SDL_DestroyWindow(window);
        }

        SDL_Window * Window::getWindow()
        {
            return window;
        }

        MATH::Rect &Window::getSize()
        {
            return size;
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