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

bool IGUIObject::hasParent()
{
    if(this->parent != nullptr)
    {
        return true;
    }
    return false;
}

void IGUIObject::setParent(IGUIObject * object)
{
    object->removeChild();
    object->setChild(this);
    this->parent = object;
}

IGUIObject * IGUIObject::getParent()
{
    return this->parent;
}

void IGUIObject::removeParent()
{
    this->parent = nullptr;
}

bool IGUIObject::hasChild()
{
    if(this->child != nullptr)
    {
        return true;
    }
    return false;
}

void IGUIObject::setChild(IGUIObject * object)
{
    object->removeParent();
    object->setParent(this);
    this->child = object;
}

IGUIObject * IGUIObject::getChild()
{
    return this->child;
}

void IGUIObject::removeChild()
{
    this->child = nullptr;
}

bool IGUIObject::hasNext()
{
    if(this->next != nullptr)
    {
        return true;
    }
    return false;
}

void IGUIObject::setNext(IGUIObject * object)
{
    object->setPrev(this);
    this->next = object;
}

IGUIObject * IGUIObject::getNext()
{
    return this->next;
}

void IGUIObject::removeNext()
{
    this->next = nullptr;
}

bool IGUIObject::hasPrev()
{
    if(this->prev != nullptr)
    {
        return true;
    }
    return false;
}

void IGUIObject::setPrev(IGUIObject * object)
{
    object->setNext(this);
    this->prev = object;
}

IGUIObject * IGUIObject::getPrev()
{
    return this->prev;
}

void IGUIObject::removePrev()
{
    this->prev = nullptr;
}

void IGUIObject::setDragable(bool dragable)
{
    this->is_dragable = dragable;
}

void IGUIObject::setPosition(Point position)
{
    Rectangle rect = Rectangle(position.getX(), position.getY(), this->dimension.getWidth(),
                               this->dimension.getHeight());
    this->dimension = rect;
}

void IGUIObject::setSize(Rectangle dimension)
{
    this->dimension = dimension;
}

Rectangle IGUIObject::getSize()
{
    return this->dimension;
}

IGUIObject::~IGUIObject()
{

}

Widget::Widget(Rectangle dimension)
    : IGUIObject(dimension)
{

}

void Widget::addWidget(Widget * w)
{
    this->setChild(w);
    w->setParent(this);
}

void Widget::removeWidget()
{
    this->getChild()->removeParent();
    this->removeChild();
}

Widget::~Widget()
{

}

ILayoutWidget::ILayoutWidget()
    : Widget()
{

}

void ILayoutWidget::addWidget(Widget * w)
{

}

void ILayoutWidget::removeWidget(Widget * w)
{

}

void ILayoutWidget::removeWidget()
{

}

ILayoutWidget::~ILayoutWidget()
{

}
