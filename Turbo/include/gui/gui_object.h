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
    *** @enum HAlignment
    **/
    enum class HAlignment : Uint8
    {
        LEFT    = 0,
        CENTER  = 1,
        RIGHT   = 2
    };

    /**
    *** @enum VAlignment
    **/
    enum class VAlignment : Uint8
    {
        CENTER  = 0,
        TOP     = 1,
        BOTTOM  = 2
    };

    /**
    *** @enum Adjustment
    **/
    enum class Adjustment : Uint8
    {
        FILL    = 0,
        NORMAL  = 1
    };

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
        const string            TAG     = "IGUIObject";
        IGUIObject            * parent  = nullptr;
        IGUIObject            * child   = nullptr;
        IGUIObject            * next    = nullptr;
        IGUIObject            * prev    = nullptr;
        std::vector<Texture>    textures;

    protected:
        bool                    is_resized          = false;
        bool                    is_dragable         = false;
        GEOMETRY::Rectangle     dimension           = GEOMETRY::Rectangle();
        HAlignment              h_align             = HAlignment::LEFT;
        VAlignment              v_align             = VAlignment::CENTER;
        Adjustment              adjustment          = Adjustment::FILL;
        Uint16                  margin[4]           = {0, 0, 0, 0};
        Uint16                  padding[4]          = {0, 0, 0, 0};
        SDL_Color               background_color    = {0, 0, 0, 0};
        SDL_Color               border_color        = {0, 0, 0, 0};
        SDL_Color               text_color          = {0, 0, 0, 255};

    public:
        IGUIObject(GEOMETRY::Rectangle dimension = GEOMETRY::Rectangle());
        //virtual void            update() = 0;
        virtual void            draw(IRenderer & renderer);
        virtual bool            hasParent();
        virtual void            setParent(IGUIObject * object);
        virtual IGUIObject    * getParent();
        virtual void            removeParent();
        virtual bool            hasChild();
        virtual void            setChild(IGUIObject * object);
        virtual IGUIObject    * getChild();
        virtual void            removeChild();
        virtual bool            hasNext();
        virtual void            setNext(IGUIObject * object);
        virtual IGUIObject    * getNext();
        virtual void            removeNext();
        virtual bool            hasPrev();
        virtual void            setPrev(IGUIObject * object);
        virtual IGUIObject    * getPrev();
        virtual void            removePrev();
        virtual void            setDragable(bool dragable);
        virtual void            setPosition(GEOMETRY::Point position);
        virtual void            setSize(GEOMETRY::Rectangle dimension);
        virtual GEOMETRY::Rectangle getSize();
        ~IGUIObject();
    };

    /**
    *** @class  Widget
    ***
    *** @brief  The class Widget represents interactive items such as a button,
    ***         combobox a.o., it is also the base class for ILayoutWidget
    **/
    class Widget : public IGUIObject
    {
    private:
        const string            TAG = "Widget";

    protected:

    public:
        Widget(GEOMETRY::Rectangle dimension = GEOMETRY::Rectangle());
        virtual void            addWidget(Widget * w);
        virtual void            removeWidget();
        ~Widget();
    };

    /**
    *** @class  ILayoutWidget
    ***
    *** @brief  The ILayoutWidget is the base class for all layout widgets
    **/
    class ILayoutWidget : public Widget
    {
    private:
        const string            TAG = "ILayoutWidget";

    protected:

    public:
        ILayoutWidget();
        virtual void            addWidget(Widget * w);
        virtual void            removeWidget(Widget * w);
        virtual void            removeWidget();
        ~ILayoutWidget();
    };

}

#endif // GUI_OBJECT_H_INCLUDED
