#ifndef GUI_WIDGET_H_INCLUDED
#define GUI_WIDGET_H_INCLUDED

/**
*** @package 	gui_widget
*** @author		Christoph Zorn
*** @date		24.02.2017
***
*** @brief		The gui_widget package contains all UI layout widgets:
***
***
**/

#include "gui/gui_object.h"

namespace GUI
{
    /**
    *** @class  Overlay
    ***
    *** @brief  This should be the base widget of the application which will distribute
    ***         all events to its children.
    **/
    class Overlay : public Widget
    {
    private:
        const std::string TAG = "Overlay";

    protected:

    public:
        Overlay(std::string xml_file);
        ~Overlay();
    };

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
        Button(std::string title = "", GEOMETRY::Rectangle dimension = GEOMETRY::Rectangle());
        Button(std::string title, int x, int y, int w, int h);
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
        Label(std::string title = "", GEOMETRY::Rectangle dimension = GEOMETRY::Rectangle());
        Label(std::string title, int x, int y, int w, int h);
        ~Label();
    };

    /**
    *** @class Input
    ***
    *** @brief
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
    *** @class  RadioButton
    ***
    *** @brief
    **/
    class RadioButton : public Widget
    {
    private:
        const std::string TAG = "RadioButton";

    protected:

    public:
        RadioButton();
        ~RadioButton();
    };

    /**
    *** @class  Checkbox
    ***
    *** @brief
    **/
    class Checkbox : public Widget
    {
    private:
        const std::string TAG = "Checkbox";

    protected:

    public:
        Checkbox();
        ~Checkbox();
    };

    /**
    *** @class  Frame
    ***
    *** @brief
    **/
    class Frame : public Widget
    {
    private:
        const std::string TAG = "Frame";

    protected:

    public:
        Frame();
        ~Frame();
    };

    /**
    *** @class  VBox
    ***
    *** @brief
    **/
    class VBox : public ILayoutWidget
    {
    private:
        const std::string TAG = "VBox";

    public:
        VBox();
        ~VBox();
    };

    /**
    *** @class  HBox
    ***
    *** @brief
    **/
    class HBox : public ILayoutWidget
    {
    private:
        const std::string TAG = "HBox";

    public:
        HBox();
        ~HBox();
    };

    /**
    *** @class List
    ***
    *** @var
    **/
    class List : public ILayoutWidget
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
    class Table : public ILayoutWidget
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
    class Grid : public ILayoutWidget
    {
    private:
        const std::string TAG = "Grid";

    protected:

    public:
        Grid();
        ~Grid();
    };

    /*
        combobox
        slider
        scrollbar
        tabwidget
    */

}

#endif // GUI_WIDGET_H_INCLUDED
