#include "gui/gui_widget.h"

using namespace GUI;
using GEOMETRY::Rectangle;

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