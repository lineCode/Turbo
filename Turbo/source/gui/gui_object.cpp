#include "gui/gui_object.h"

using namespace GUI;
using GEOMETRY::Rectangle;
using GEOMETRY::Point;
using EXTERN::XML;

IGUIObject::IGUIObject(Rectangle dimension)
    : dimension(dimension)
{

}

IGUIObject::IGUIObject(int x, int y, int w, int h)
    : dimension(Rectangle(x, y, w, h))
{

}

void IGUIObject::onMouseover(std::function<void()>callback)
{
    //this->registerEvent(SDL_MOUSEMOTION, 30, callback);
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
    XML widget              = xml.findTag("Widget");
    XML style               = widget.findTag("Style");
    XML margin              = style.findTag("margin");
    XML padding             = style.findTag("padding");
    XML border              = style.findTag("border");
    XML background_color    = style.findTag("background_color");
    XML border_color        = style.findTag("border_color");
    XML text_color          = style.findTag("text_color");

    this->dimension = Rectangle(widget.getValueAsInt("x"), widget.getValueAsInt("y"),
                                widget.getValueAsInt("w"), widget.getValueAsInt("h"));

    this->margin[0] = margin.getValueAsInt("t");
    this->margin[1] = margin.getValueAsInt("r");
    this->margin[2] = margin.getValueAsInt("b");
    this->margin[3] = margin.getValueAsInt("l");

    this->padding[0] = padding.getValueAsInt("t");
    this->padding[1] = padding.getValueAsInt("r");
    this->padding[2] = padding.getValueAsInt("b");
    this->padding[3] = padding.getValueAsInt("l");

    this->border[0] = border.getValueAsInt("t");
    this->border[1] = border.getValueAsInt("r");
    this->border[2] = border.getValueAsInt("b");
    this->border[3] = border.getValueAsInt("l");

    this->border_color.r = border_color.getValueAsInt("r");
    this->border_color.g = border_color.getValueAsInt("g");
    this->border_color.b = border_color.getValueAsInt("b");
    this->border_color.a = border_color.getValueAsInt("a");

    this->background_color.r = background_color.getValueAsInt("r");
    this->background_color.g = background_color.getValueAsInt("g");
    this->background_color.b = background_color.getValueAsInt("b");
    this->background_color.a = background_color.getValueAsInt("a");

    this->text_color.r = text_color.getValueAsInt("r");
    this->text_color.g = text_color.getValueAsInt("g");
    this->text_color.b = text_color.getValueAsInt("b");
    this->text_color.a = text_color.getValueAsInt("a");
}

XML IGUIObject::getStyle()
{
    XML widget = XML(this->TAG);
    widget.kvp["x"] = this->dimension.getX();
    widget.kvp["y"] = this->dimension.getY();
    widget.kvp["w"] = this->dimension.getWidth();
    widget.kvp["h"] = this->dimension.getLength();

    XML style;
    XML margin = XML("margin", true);
    margin.kvp["t"] = this->margin[0];
    margin.kvp["r"] = this->margin[1];
    margin.kvp["b"] = this->margin[2];
    margin.kvp["l"] = this->margin[3];

    XML padding = XML("padding", true);
    padding.kvp["t"] = this->padding[0];
    padding.kvp["r"] = this->padding[1];
    padding.kvp["b"] = this->padding[2];
    padding.kvp["l"] = this->padding[3];

    XML border = XML("border", true);
    border.kvp["t"] = this->border[0];
    border.kvp["r"] = this->border[1];
    border.kvp["b"] = this->border[2];
    border.kvp["l"] = this->border[3];

    XML border_color = XML("border_color", true);
    border_color.kvp["r"] = this->border_color.r;
    border_color.kvp["g"] = this->border_color.g;
    border_color.kvp["b"] = this->border_color.b;
    border_color.kvp["a"] = this->border_color.a;

    XML background_color = XML("background_color", true);
    background_color.kvp["r"] = this->background_color.r;
    background_color.kvp["g"] = this->background_color.g;
    background_color.kvp["b"] = this->background_color.b;
    background_color.kvp["a"] = this->background_color.a;

    XML text_color = XML("text_color", true);
    text_color.kvp["r"] = this->text_color.r;
    text_color.kvp["g"] = this->text_color.g;
    text_color.kvp["b"] = this->text_color.b;
    text_color.kvp["a"] = this->text_color.a;

    style.children.push_back(&text_color);
    style.children.push_back(&background_color);
    style.children.push_back(&border_color);
    style.children.push_back(&border);
    style.children.push_back(&padding);
    style.children.push_back(&margin);

    widget.children.push_back(&style);

    return widget;
}

IGUIObject::~IGUIObject()
{

}

Widget::Widget(Rectangle dimension)
    : IGUIObject(dimension)
{

}

Widget::Widget(int x, int y, int w, int h)
    : IGUIObject(x, y, w, h)
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
