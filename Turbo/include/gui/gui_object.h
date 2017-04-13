#ifndef GUI_OBJECT_H_INCLUDED
#define GUI_OBJECT_H_INCLUDED

/**
*** @package    gui_object
*** @author     Christoph Zorn
*** @date       24.02.2017
***
*** @brief      The module gui contains
***
***
**/

#include "gui/gui.h"

namespace GUI
{
    /**
    *** @class IGUIObject
    ***
    *** @brief This is the base class for all objects that are drawn above the game
    ***        screen. Every base object can only contain one child object.
    ***
    *** @var
    **/
    class IGUIObject
    {
    private:
        const string        TAG     = "IGUIObject";
        IGUIObject        * parent  = nullptr;
        IGUIObject        * child   = nullptr;
        IGUIObject        * next    = nullptr;
        IGUIObject        * prev    = nullptr;
        std::vector<Texture> textures;

    protected:
        bool                size_changed;
        GEOMETRY::Rectangle dimension;
        Uint32              margin[4];
        Uint32              padding[4];
        SDL_Color           background_color;
        SDL_Color           border_color;
        SDL_Color           text_color;

    public:
        IGUIObject(GEOMETRY::Rectangle dimension);
        virtual void        update() = 0;
        virtual void        draw(IRenderer & renderer);
        virtual void        setParent(IGUIObject * object);
        virtual void        setChild(IGUIObject * object);
        virtual void        setNext(IGUIObject * object);
        virtual void        setPrev(IGUIObject * object);
        virtual void        setDragable(bool dragable);
        virtual void        setPosition(GEOMETRY::Point position);
        virtual void        resize(GEOMETRY::Rectangle dimension);
        ~IGUIObject();
    };

    /**
    *** @class  Widget
    ***
    *** @brief  The class Widget represents interactive layout items such as a button, combobox a.o.
    **/
    class Widget : protected IGUIObject
    {
    private:
        const string        TAG = "Widget";

    protected:

    public:
        Widget(GEOMETRY::Rectangle dimension);
        virtual void        addWidget(Widget * w) = 0;
        virtual void        removeWidget(Widget * w) = 0;
        ~Widget();
    };

}

#endif // GUI_OBJECT_H_INCLUDED
