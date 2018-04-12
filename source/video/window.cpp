#include "video/window.h"

namespace TURBO
{
    namespace VIDEO
    {
        Window::Window(const std::string &title, MATH::Rect geometry, Uint32 flags)
            : geometry(geometry)//, SCRIPT::LuaObject(__FUNCTION__)
        {
            if(SYSTEM::SDL::SDL_IS_INIT)
            {
                window = SDL_CreateWindow(title.c_str(), geometry.x, geometry.y, geometry.w, geometry.h, flags);

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

        MATH::Rect &Window::getGeometry()
        {
            return geometry;
        }

        MATH::Rect &Window::setGeometry(MATH::Rect rect)
        {
            setPosition(rect.topLeft());
            setSize(rect);
            return geometry;
        }

        MATH::Point Window::getPosition()
        {
            return {geometry.x, geometry.y};
        }

        MATH::Point Window::setPosition(MATH::Point point)
        {
            geometry = MATH::Rect(point.x, point.y, geometry.w, geometry.h);
            SDL_SetWindowPosition(window, geometry.x, geometry.y);
        }

        MATH::Rect Window::getSize()
        {
            return {0, 0, geometry.w, geometry.h};
        }

        MATH::Rect Window::setSize(MATH::Rect rect)
        {
            geometry = MATH::Rect(geometry.x, geometry.y, rect.w, rect.h);
            SDL_SetWindowSize(window, geometry.w, geometry.h);
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

        void Window::registerObject(lua_State *state)
        {
            luabridge::getGlobalNamespace(state)
                .beginNamespace("VIDEO")
                    .beginClass<Window>("Window")
                    .addConstructor<void(*)(std::string, MATH::Rect, Uint32)>()
                    .addFunction("setGeometry", &Window::setGeometry)
                    .endClass()
                .endNamespace();
        }
    }
}