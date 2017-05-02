#include "gui/gui_object.h"

using namespace GUI;
using GEOMETRY::Rectangle;
using GEOMETRY::Point;
using EXTERN::XML;

IGUIObject::IGUIObject(Rectangle dimension)
    : dimension(dimension)
{

}

void IGUIObject::update()
{


    if(this->hasChild())
    {
        this->child->update();
    }
}

void IGUIObject::draw(IRenderer & renderer)
{
    SDL_Rect rect = this->dimension.toSDL_Rect();

    renderer.setDrawColor(this->background_color);
    SDL_RenderFillRect(renderer.getRenderer(), &rect);
    renderer.setDrawColor(this->border_color);
    SDL_RenderDrawRect(renderer.getRenderer(), &rect);
    renderer.setDrawColor(renderer.getResetColor());


    if(this->child != nullptr)
    {
        this->child->draw(renderer);
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
    this->child = object;
    object->setPosition(this->getPosition());
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
    this->update();
}

Point IGUIObject::getPosition()
{
    Point p = Point(this->dimension.getX(), this->dimension.getY());
    return p;
}

void IGUIObject::setSize(Rectangle dimension)
{
    this->dimension = dimension;
    this->update();
}

Rectangle IGUIObject::getSize()
{
    return this->dimension;
}

void IGUIObject::setMargin(Uint16 t, Uint16 r, Uint16 b, Uint16 l)
{
    this->margin = {t, r, b, l};
    this->update();
}

std::vector<Uint16> IGUIObject::getMargin()
{
    return this->margin;
}

void IGUIObject::setPadding(Uint16 t, Uint16 r, Uint16 b, Uint16 l)
{
    this->padding = {t, r, b, l};
    this->update();
}

std::vector<Uint16> IGUIObject::getPadding()
{
    return this->padding;
}

void IGUIObject::setBorder(Uint8 t, Uint8 r, Uint8 b, Uint8 l)
{
    this->border = {t, r, b, l};
    this->update();
}

std::vector<Uint8> IGUIObject::getBorder()
{
    return this->border;
}

void IGUIObject::setBackgroundColor(Color color)
{
    this->background_color = color;
}

Color IGUIObject::getBackroundColor()
{
    return this->background_color;
}

void IGUIObject::setTextColor(Color color)
{
    this->text_color = color;
}

Color IGUIObject::getTextColor()
{
    return this->text_color;
}

void IGUIObject::setBorderColor(Color color)
{
    this->border_color = color;
}

Color IGUIObject::getBorderColor()
{
    return this->border_color;
}

void IGUIObject::setHAlignment(HAlignment alignment)
{
    this->h_align = alignment;
}

HAlignment IGUIObject::getHAlignment()
{
    return this->h_align;
}

void IGUIObject::setVAlignment(VAlignment alignment)
{
    this->v_align = alignment;
    this->update();
}

VAlignment IGUIObject::getVAlignment()
{
    return this->v_align;
}

void IGUIObject::setAdjustment(Adjustment ajdustment)
{
    this->adjustment = adjustment;

}

Adjustment IGUIObject::getAdjustment()
{
    return this->adjustment;
}

void IGUIObject::setStyle(XML xml)
{
    this->dimension = Rectangle(xml.getValueAsInt("x"), xml.getValueAsInt("y"),
                                xml.getValueAsInt("w"), xml.getValueAsInt("h"));

    XML style = xml.findTag("Style");

}

XML IGUIObject::getStyle()
{
    XML xml;

    xml.tag = this->TAG;
    xml.kvp["x"] = this->dimension.getX();
    xml.kvp["y"] = this->dimension.getY();
    xml.kvp["w"] = this->dimension.getWidth();
    xml.kvp["h"] = this->dimension.getLength();
/*
    XML * style;

    xml.children.push_back(style);
*/
    return xml;
}

IGUIObject::~IGUIObject()
{

}

Widget::Widget(Rectangle dimension)
    : IGUIObject(dimension)
{

}

Widget::Widget(std::string xml_file)
    : IGUIObject()
{
	if(EXTERN::Directory::isType(xml_file, "xml"))
	{
        EXTERN::XMLParser parser(xml_file);
        XML xml = parser.getXML();
        XML w = xml.findTag("Widget");
        if(!w.isEmpty())
        {
            this->setStyle(w);
        }
        else
        {
            UTILS::Log::warning(this->TAG, "No Widget Tag found in file " + xml_file,
                                UTILS::LOG_TYPE::WARNING);
        }
	}
	else
    {
        UTILS::Log::warning(this->TAG, "Failed to load file " + xml_file, UTILS::LOG_TYPE::WARNING);
    }
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
