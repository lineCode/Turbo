#ifndef GUI_WIDGET_H_INCLUDED
#define GUI_WIDGET_H_INCLUDED

#include "gui/gui_object.h"

namespace GUI
{
    /**
    *** @class Button
    ***
    *** @var
    **/
    class Button : public Widget
    {
    private:
        const std::string TAG = "Button";

    protected:

    public:
        Button(std::string title);
        ~Button();
    };

    /**
    *** @class Label
    ***
    *** @var
    **/
    class Label : public Widget
    {
    private:
        const std::string TAG = "Label";

    protected:

    public:
        Label(std::string title);
        ~Label();
    };

    /**
    *** @class Input
    ***
    *** @var
    **/
    class Input : public Widget
    {
    private:
        const std::string TAG = "Input";

    protected:

    public:
        Input();
        ~Input();
    };

    /**
    *** @class List
    ***
    *** @var
    **/
    class List : public Widget
    {
    private:
        const std::string TAG = "List";

    protected:

    public:
        List();
        ~List();
    };

    /**
    *** @class Table
    ***
    *** @var
    **/
    class Table : public Widget
    {
    private:
        const std::string TAG = "Table";

    protected:

    public:
        Table();
        ~Table();
    };

    /**
    *** @class Grid
    ***
    *** @var
    **/
    class Grid : public Widget
    {
    private:
        const std::string TAG = "Grid";

    protected:

    public:
        Grid();
        ~Grid();
    };

}

#endif // GUI_WIDGET_H_INCLUDED
