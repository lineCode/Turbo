#include "gui/gui_object.h"

using namespace GUI;

IGUIObject::IGUIObject(Rectangle dimension)
{

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

void IGUIObject::setPosition(GEOMETRY::Point position)
{

}

void IGUIObject::setDragable(bool dragable)
{

}

void IGUIObject::resize(GEOMETRY::Rectangle dimension)
{

}

IGUIObject::~IGUIObject()
{

}

Widget::Widget()
	: IGUIObject(GEOMETRY::Rectangle())
{

}

Widget::~Widget()
{

}