#include "geometry/geometry.h"

using namespace GEOMETRY;

Point::Point()
{

}

Point::Point(double x)
    : x(x)
{

}

Point::Point(double x, double y)
    : x(x), y(y)
{

}

Point::Point(double x, double y, double z)
    : x(x), y(y), z(z)
{

}

Point Point::operator+(Point p)
{
    Point pr = Point();

    pr.setX(this->x + p.getX());
    pr.setY(this->y + p.getY());
    pr.setZ(this->z + p.getZ());

    return pr;
}

Point Point::operator*(double factor)
{
    Point p = Point();

    p.setX(this->x * factor);
    p.setY(this->y * factor);
    p.setZ(this->z * factor);

    return p;
}

Point Point::operator*(Point p)
{
    Point pr = Point();

    pr.setX(this->x * p.getX());
    pr.setY(this->y * p.getY());
    pr.setZ(this->z * p.getZ());

    return pr;
}

void Point::add(double x)
{
    this->x += x;
}

void Point::add(double x, double y)
{
    this->x += x;
    this->y += y;
}

void Point::add(double x, double y, double z)
{
    this->x += x;
    this->y += y;
    this->z += z;
}

void Point::setX(double x)
{
    this->x = x;
}

double Point::getX()
{
    return this->x;
}

void Point::setY(double y)
{
    this->y = y;
}

double Point::getY()
{
    return this->y;
}

void Point::setZ(double z)
{
    this->z = z;
}

double Point::getZ()
{
    return this->z;
}

double Point::getDistance(Point p)
{
    return sqrt(pow(this->x-p.getX(), 2.0) + pow(this->y-p.getY(), 2.0) + pow(this->z-p.getZ(), 2.0));
}

SDL_Point Point::toSDL_Point()
{
    SDL_Point p;
    p.x = this->x;
    p.y = this->y;
    return p;
}

Point::~Point()
{

}

Line::Line()
    : p1(0, 0, 0), p2(0, 0, 0)
{

}

Line::Line(Point p1, Point p2)
    : p1(p1), p2(p2)
{

}

Line::Line(double x1, double y1, double x2, double y2)
    : p1(x1, y1), p2(x2, y2)
{

}

void Line::setX(double x)
{
    this->p1.setX(x);
}

double Line::getX()
{
    return this->p1.getX();
}

void Line::setY(double y)
{
    this->p1.setY(y);
}

double Line::getY()
{
    return this->p1.getY();
}

void Line::setWeight(double w)
{
    this->weight = w;
}

double Line::getWeight()
{
    return this->weight;
}

double Line::getLength()
{
    return p1.getDistance(p2);
}

Point Line::getFirst()
{
    return this->p1;
}

Point Line::getSecond()
{
    return this->p2;
}

Line::~Line()
{

}

IShape::IShape()
{

}

vector<Point> IShape::getVertices()
{
    return this->vertices;
}

vector<Line> IShape::getEdges()
{
    return this->edges;
}

Point IShape::getVertice(Uint16 i)
{
    Point p = Point();
    if(this->vertices.size() <= i)
    {
        p = this->vertices.at(i);
    }
    return p;
}

Line IShape::getEdge(Uint16 i)
{
    Line l = Line();
    if(this->edges.size() <= i)
    {
        l = this->edges.at(i);
    }
    return l;
}

bool IShape::isEmpty()
{
    bool isEmpty = false;

    if(this->vertices.size() == 0 && this->edges.size() == 0)
    {
        isEmpty = true;
    }
    return isEmpty;
}

IShape::~IShape()
{

}

Triangle::Triangle()
    : IShape(), p1(0, 0, 0), p2(0, 0, 0), p3(0, 0, 0)
{

}

Triangle::Triangle(Point p1, Point p2, Point p3)
    : p1(p1), p2(p2), p3(p3)
{

}

void Triangle::setX(double x)
{
    this->p1.setX(x);
}

double Triangle::getX()
{
    return this->p1.getX();
}

void Triangle::setY(double y)
{
    this->p1.setY(y);
}

double Triangle::getY()
{
    return this->p1.getY();
}

double Triangle::getWidth()
{
    double left = min(min(p1.getX(), p2.getX()), p3.getX());
    double right = max(max(p1.getX(),p2.getX()), p3.getX());
    return abs(left - right);
}

double Triangle::getLength()
{
    double top = min(min(p1.getY(), p2.getY()), p3.getY());
    double bot = max(max(p1.getY(), p2.getY()), p3.getY());
    return abs(top - bot);
}

double Triangle::getHeight()
{
    return 0;
}

double Triangle::getArea()
{
	return abs(p1.getX() * (p2.getY() - p3.getY())
             + p2.getX() * (p3.getY() - p1.getY())
			 + p3.getX() * (p1.getY() - p2.getY()));
}

double Triangle::getScope()
{
    return p1.getDistance(p2) + p2.getDistance(p3) + p3.getDistance(p1);
}

double Triangle::getVolume()
{
    return 0;
}

Triangle::~Triangle()
{

}

Rectangle::Rectangle()
    : IShape(), p1(0, 0, 0), p2(0, 0, 0), p3(0, 0, 0), p4(0, 0, 0)
{

}

Rectangle::Rectangle(Point p1, Point p2, Point p3, Point p4)
    : IShape(), p1(p1), p2(p2), p3(p3), p4(p4)
{

}

Rectangle::Rectangle(double x, double y, double w, double h)
    : IShape(), p1(x, y), p2(x+w, y), p3(x+w, y+h), p4(x, y+h)
{

}

void Rectangle::setX(double x)
{
    this->p1.setX(x);
}

double Rectangle::getX()
{
    return this->p1.getX();
}

void Rectangle::setY(double y)
{
    this->p1.setY(y);
}

double Rectangle::getY()
{
    return this->p1.getY();
}

void Rectangle::setWidth(double w)
{
    this->p2.setX(w);
    this->p3.setX(w);
}

double Rectangle::getWidth()
{
    double left = min(min(min(p1.getX(), p2.getX()), p3.getX()), p4.getX());
    double right = max(max(max(p1.getX(), p2.getX()), p3.getX()), p4.getX());
    return abs(left - right);
}

void Rectangle::setLength(double l)
{
    this->p3.setY(l);
    this->p4.setY(l);
}

double Rectangle::getLength()
{
    double top = min(min(min(p1.getY(), p2.getY()), p3.getY()), p4.getY());
    double bot = max(max(max(p1.getY(), p2.getY()), p3.getY()), p4.getY());
    return abs(top - bot);
}

void Rectangle::setHeight(double h)
{

}

double Rectangle::getHeight()
{
    return 0;
}

void Rectangle::setArea(double a)
{

}

double Rectangle::getArea()
{
    return (this->getEdges().at(0).getLength() * this->getEdges().at(1).getLength());
}

void Rectangle::setScope(double s)
{

}

double Rectangle::getScope()
{
    return 2*(this->getEdges().at(0).getLength() + this->getEdges().at(1).getLength());
}

void Rectangle::setVolume(double v)
{

}

double Rectangle::getVolume()
{
    return 0;
}

SDL_Rect Rectangle::toSDL_Rect()
{
    SDL_Rect rect;
    rect.x = this->p1.getX();
    rect.y = this->p1.getY();
    rect.w = this->p3.getX();
    rect.h = this->p3.getY();
    return rect;
}

Rectangle::~Rectangle()
{

}