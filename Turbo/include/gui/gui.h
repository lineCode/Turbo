#ifndef GUI_H_INCLUDED
#define GUI_H_INCLUDED

/**
*** @module     gui
*** @author     Christoph Zorn
*** @date       24.02.2017
***
*** @brief      The module gui contains
***
***
**/

#include "geometry/geometry.h"

namespace GUI
{
    //TODO
    typedef int PLACEHOLDER;

    /**
    *** @class Window
    ***
    *** @var
    **/
    class Window
    {
    private:
        const string TAG = "Window";

    protected:

    public:
        Window();
        ~Window();
    };


    /**
    *** @class IRenderer
    ***
    *** @var
    **/
    template <typename T>
    class IRenderer
    {
    private:
        const string    TAG = "IRenderer";

    protected:
        std::list<T>    scene_objects;

    public:
        IRenderer(Window & window);
        ~IRenderer();
    };

    /**
    *** @class GUIRenderer
    ***
    *** @var
    **/
    class GUIRenderer : public IRenderer<PLACEHOLDER>
    {
    private:
        const string TAG = "GUIRenderer";

    protected:

    public:
        GUIRenderer();
        ~GUIRenderer();
    };

    /**
    *** @class GameRenderer
    ***
    *** @var
    **/
    class GameRenderer : public IRenderer<PLACEHOLDER>
    {
    private:
        const string TAG = "GameRenderer";

    protected:

    public:
        GameRenderer();
        ~GameRenderer();
    };

}

#endif // GUI_H_INCLUDED
