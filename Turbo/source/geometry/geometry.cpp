#include "geometry/geometry.h"

using namespace GEOMETRY;

Point::Point()
{

}

Point::Point(Point & p)
{
    this = &p;
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

double Point::getX()
{
    return this->x;
}

double Point::getY()
{
    return this->y;
}

double Point::getZ()
{
    return this->z;
}

double Point::getDistance(Point p)
{
    return sqrt(pow(this->x-p.getX(), 2.0), pow(this->y-p.getY(), 2.0), pow(this->z-p.getZ(), 2.0));
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
    : p1(0, 0, 0), p2(0, 0, 0), p3(0, 0, 0)
{

}

Triangle::Triangle(Triangle & t)
{
    this = &t;
}

Triangle::Triangle(Point p1, Point p2, Point p3)
    : p1(p1), p2(p2), p3(p3)
{

}

double Triangle::getWidth()
{
    double left = min(min(p1.getX() < p2.getX()), p3.getX());
    double right = max(max(p1.getX() < p2.getX()), p3.getX());
    return abs(left - right);
}

double Triangle::getLength()
{
    double top = min(min(p1.getY() < p2.getY()), p3.getY());
    double bot = max(max(p1.getY() < p2.getY()), p3.getY());
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
    : p1(0, 0, 0), p2(0, 0, 0), p3(0, 0, 0), p4(0, 0, 0)
{

}

Rectangle::Rectangle(Rectangle & r)
{
    this = &r;
}

Rectangle(Point p1, Point p2, Point p3, Point p4)
    : p1(p1), p2(p2), p3(p3), p4(p4)
{

}

Rectangle::Rectangle(double x, double y, double w, double h)
    : p1(x, y), p2(x+w, y), p3(x+w, y+h), p4(x, y+h)
{

}

double Rectangle::getWidth()
{
    double left = min(min(p1.getX() < p2.getX()), p3.getX());
    double right = max(max(p1.getX() < p2.getX()), p3.getX());
    return abs(left - right);
}

double Rectangle::getLength()
{
    double top = min(min(p1.getY() < p2.getY()), p3.getY());
    double bot = max(max(p1.getY() < p2.getY()), p3.getY());
    return abs(top - bot);
}

double Rectangle::getHeight()
{
    return 0;
}

double Rectangle::getArea()
{
    return (this->edges.at(0).getLength() * this->edges.at(1).getLength());
}

double Rectangle::getScope()
{
    return 2*(length + width);
}

double Rectangle::getVolume()
{
    return 0;
}

Rectangle::~Rectangle()
{

}