#include "gui/gui_widget.h"

using namespace GUI;
using GEOMETRY::Rectangle;

Overlay::Overlay(string xml_file)
    : Widget(xml_file)
{

}

Overlay::~Overlay()
{

}

Button::Button(string title, Rectangle dimension)
    : Widget(dimension)
{

}

Button::~Button()
{

}

Label::Label(string title, Rectangle dimension)
    : Widget(dimension)
{

}

Label::~Label()
{

}

Input::Input()
    : Widget()
{

}

Input::~Input()
{

}

RadioButton::RadioButton()
{

}

RadioButton::~RadioButton()
{

}

Checkbox::Checkbox()
{

}

Checkbox::~Checkbox()
{

}

Frame::Frame()
{

}

Frame::~Frame()
{

}

VBox::VBox()
{

}

VBox::~VBox()
{

}

HBox::HBox()
{

}

HBox::~HBox()
{

}

List::List()
    : ILayoutWidget()
{

}

List::~List()
{

}

Table::Table()
    : ILayoutWidget()
{

}

Table::~Table()
{

}

Grid::Grid()
    : ILayoutWidget()
{

}

Grid::~Grid()
{

}