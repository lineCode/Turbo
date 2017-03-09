#include "gui/gui_object.h"

using namespace GUI;
using GEOMETRY::Rectangle;
using GEOMETRY::Point;

IGUIObject::IGUIObject(Rectangle dimension)
    : dimension(dimension)
{

}

void IGUIObject::draw(IRenderer & renderer)
{
    for(Texture texture : this->textures)
    {
        //renderer.draw(texture);
    }
}

void IGUIObject::setParent(IGUIObject * object)
{
    object->setChild(this);
    this->parent = object;
}

void IGUIObject::setChild(IGUIObject * object)
{
    object->setParent(this);
    this->child = object;
}

void IGUIObject::setNext(IGUIObject * object)
{
    object->setPrev(this);
    this->next = object;
}

void IGUIObject::setPrev(IGUIObject * object)
{
    object->setNext(this);
    this->prev = object;
}

void IGUIObject::setDragable(bool dragable)
{

}

void IGUIObject::setPosition(Point position)
{

}

void IGUIObject::resize(Rectangle dimension)
{

}

IGUIObject::~IGUIObject()
{

}

Widget::Widget(Rectangle dimension)
    : IGUIObject(dimension)
{

}

Widget::~Widget()
{

}
