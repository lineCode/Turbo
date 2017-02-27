#ifndef GUI_OBJECT_H_INCLUDED
#define GUI_OBJECT_H_INCLUDED

#include "gui/gui.h"

namespace GUI
{
    /**
    *** @class IGUIObject
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

    protected:
        bool                sizeChanged;
        GEOMETRY::Rectangle dimension;

    public:
        IGUIObject(GEOMETRY::Rectangle dimension);
        virtual void        update() = 0;
        virtual void        draw() = 0;
        virtual void        setPosition(GEOMETRY::Point position);
        virtual bool        setDragable(bool dragable);
        virtual void        resize(GEOMETRY::Rectangle dimension);
        ~IGUIObject();
    };

    /**
    *** @class Widget
    ***
    *** @var
    **/
    class Widget : protected IGUIObject
    {
    private:
        const string TAG = "Widget";

    protected:

    public:
        Widget();
        virtual void        addWidget(Widget * w) = 0;
        virtual void        removeWidget(Widget * w) = 0;
        ~Widget();
    };

}

#endif // GUI_OBJECT_H_INCLUDED
