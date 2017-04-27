#ifndef GUI_OBJECT_H_INCLUDED
#define GUI_OBJECT_H_INCLUDED

/**
*** @package    gui_object
*** @author     Christoph Zorn
*** @date       24.02.2017
***
*** @brief      The module gui_object contains the abstract definitions for display
***             overlays
***
***
**/

#include "gui/gui.h"

namespace GUI
{

    /**
    *** @enum HAlignment
    ***
    *** @brief  Describes the horizontal alignment of a widget
    **/
    enum class HAlignment : Uint8
    {
        LEFT    = 0,
        CENTER  = 1,
        RIGHT   = 2
    };

    /**
    *** @enum   VAlignment
    ***
    *** @brief  Describes the vertical alignment of a widget
    **/
    enum class VAlignment : Uint8
    {
        CENTER  = 0,
        TOP     = 1,
        BOTTOM  = 2
    };

    /**
    *** @enum   Adjustment
    ***
    *** @brief  The enum Adjustment describes the behavior of a widget within another
    ***         widget
    **/
    enum class Adjustment : Uint8
    {
        MAXIMUM     = 0,    // use all available space
        NORMAL      = 1,    // use the absolute dimensions if they are fitting
        MINIMUM     = 2     // use the minimal required space
    };

    /**
    *** @class  IGUIObject
    ***
    *** @brief  This is the base class for all gui objects.
    ***         Every base object can only contain one child object.
    ***
    *** @var
    **/
    class IGUIObject
    {
    private:
        const std::string       TAG     = "IGUIObject";
        IGUIObject            * parent  = nullptr;
        IGUIObject            * child   = nullptr;
        IGUIObject            * next    = nullptr;
        IGUIObject            * prev    = nullptr;
        std::vector<Texture>    textures;

    protected:
        // Style Properties
        bool                    is_dragable         = false;
        GEOMETRY::Rectangle     dimension           = GEOMETRY::Rectangle();
        HAlignment              h_align             = HAlignment::LEFT;
        VAlignment              v_align             = VAlignment::CENTER;
        Adjustment              adjustment          = Adjustment::MAXIMUM;
        std::vector<Uint16>     margin              = {0, 0, 0, 0};
        std::vector<Uint16>     padding             = {0, 0, 0, 0};
        std::vector<Uint8>      border              = {0, 0, 0, 0};
        Color                   background_color    = {0, 0, 0, 0};
        Color                   border_color        = {0, 0, 0, 0};
        Color                   text_color          = {0, 0, 0, 255};

    public:
        IGUIObject(GEOMETRY::Rectangle dimension = GEOMETRY::Rectangle());
        virtual void            update();
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
        virtual GEOMETRY::Point getPosition();
        virtual void            setSize(GEOMETRY::Rectangle dimension);
        virtual GEOMETRY::Rectangle getSize();
        virtual void            setMargin(Uint16 t, Uint16 r, Uint16 b, Uint16 l);
        virtual std::vector<Uint16> getMargin();
        virtual void            setPadding(Uint16 t, Uint16 r, Uint16 b, Uint16 l);
        virtual std::vector<Uint16> getPadding();
        virtual void            setBorder(Uint8 t, Uint8 r, Uint8 b, Uint8 l);
        virtual std::vector<Uint8> getBorder();
        virtual void            setBackgroundColor(Color color);
        virtual Color           getBackroundColor();
        virtual void            setTextColor(Color color);
        virtual Color           getTextColor();
        virtual void            setBorderColor(Color color);
        virtual Color           getBorderColor();
        virtual void            setHAlignment(HAlignment alignment);
        virtual HAlignment      getHAlignment();
        virtual void            setVAlignment(VAlignment alignment);
        virtual VAlignment      getVAlignment();
        virtual void            setAdjustment(Adjustment adjustment);
        virtual Adjustment      getAdjustment();
        virtual void            setStyle(EXTERN::XML xml);
        virtual EXTERN::XML     getStyle();
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
        const std::string            TAG = "Widget";

    protected:

    public:
        Widget(GEOMETRY::Rectangle dimension = GEOMETRY::Rectangle());
        Widget(std::string xml_file);
        virtual void            addWidget(Widget * w);
        virtual void            removeWidget();
        ~Widget();
    };

    /**
    *** @class  ILayoutWidget
    ***
    *** @brief  The ILayoutWidget is the base class for all layout widgets such as
    ***         a grid, vbox, hbox and a list
    **/
    class ILayoutWidget : public Widget
    {
    private:
        const std::string            TAG = "ILayoutWidget";

        std::vector<Widget *>   children;

    protected:

    public:
        ILayoutWidget();
        virtual void            addWidget(Widget * w);
        //virtual Widget *        getWidgets();
        virtual void            removeWidget(Widget * w);
        virtual void            removeWidget();
        ~ILayoutWidget();
    };

}

#endif // GUI_OBJECT_H_INCLUDED
