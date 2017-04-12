#ifndef GEOMETRY_H_INCLUDED
#define GEOMETRY_H_INCLUDED

#include "Turbo_main.h"

namespace GEOMETRY
{
    /**
    *** @class Point
    ***
    *** @var
    **/
    class Point
    {
    private:
        const std::string    TAG = "Point";
        double          x = 0;
        double          y = 0;
        double          z = 0;

    protected:

    public:
        Point();
        //Point(Point & p);
        Point(double x);
        Point(double x, double y);
        Point(double x, double y, double z);
        Point           operator=(Point & p);
        Point           operator+(Point p);
        Point           operator*(double factor);
        Point           operator*(Point p);
        void            add(double x);
        void            add(double x, double y);
        void            add(double x, double y, double z);
        void            setX(double x);
        double          getX();
        void            setY(double y);
        double          getY();
        void            setZ(double z);
        double          getZ();
        double          getDistance(Point p);
		bool		    isEmpty();
        ~Point();
    };

    /**
    *** @class Line
    ***
    *** @var
    **/
    class Line
    {
    private:
        const std::string    TAG = "Line";
        double          weight = 0;
        Point           p1;
		Point           p2;

    protected:

    public:
        Line();
        //Line(Line & line);
        Line(Point p1, Point p2);
		Line(double x1, double y1, double x2, double y2);
		Line            operator=(Line & l);
		void            setWeight(double w);
		double          getWeight();
		double          getLength();
		Point           getFirst();
		Point           getSecond();
        ~Line();
    };

    /**
    *** @class Vector
    ***
    *** @var
    **/
    class Vector
    {
    private:
        const std::string TAG = "Vector";

    protected:

    public:
        Vector();
        ~Vector();
    };


    /**
    *** @class IShape
    ***
    *** @brief This class represents a graph or more complex geometric structures
    ***
    *** @var
    **/
    class IShape
    {
    private:
        const string    TAG = "IShape";
        vector<Point>   vertices;
        vector<Line>    edges;
        double          width = 0;
        double          length = 0;
        double          height = 0;

    protected:

    public:
        IShape();
                vector<Point>   getVertices();
                vector<Line>    getEdges();
                Point           getVertice(Uint16 i);
                Line            getEdge(Uint16 i);
        /**
         *
         */
        virtual bool            isEmpty();

        /**
         * The greatest distance between 2 points in the x coordinate
         */
        virtual double          getWidth() = 0;

        /**
         * The greatest distance between 2 points in the y coordinate
         */
        virtual double          getLength() = 0;

        /**
         * The greatest distance between 2 points in the z coordinate
         */
        virtual double          getHeight() = 0;

        /**
         * The surface area of an object
         */
        virtual double          getArea() = 0;

        /**
         *
         * Scope of a 2D object is equivalent to the length of its edges
         */
        virtual double          getScope() = 0;

        /**
         *
         * 2D objects have no volume
         */
        virtual double          getVolume() = 0;
        ~IShape();
    };


    /**
    *** @class Triangle
    ***
    *** @var
    **/
    class Triangle : public IShape
    {
    private:
        const std::string    TAG = "Triangle";
        Point           p1;
		Point           p2;
		Point           p3;

    protected:

    public:
        Triangle();
        //Triangle(Triangle & t);
        Triangle(Point p1, Point p2, Point p3);
		Triangle(double x1, double y1, double x2, double y2, double x3, double y3);
		double          getWidth();
		double          getLength();
		double          getHeight();
        double          getArea();
        double          getScope();
        double          getVolume();
        ~Triangle();
    };

    /**
    *** @class  Rectangle
    ***
    *** @var    p1 top left
    *** @var    p2 top right
    *** @var    p3 bottom right
    *** @var    p4 bottom left
    **/
    class Rectangle : public IShape
    {
    private:
        const std::string    TAG = "Rectangle";
        Point           p1;
		Point           p2;
		Point           p3;
		Point           p4;

    protected:

    public:
        Rectangle();
        //Rectangle(Rectangle & r);
        Rectangle(Point p1, Point p2, Point p3, Point p4);
        Rectangle(double x, double y, double w, double h);
        double          setX(double x);
        double          getX();
        void            setY(double y);
        double          getY();
        void            setWidth(double w);
        double          getWidth();
		void            setLength(double l);
		double          getLength();
		void            setHeight(double h);
		double          getHeight();
        void            setArea(double a);
        double          getArea();
        void            setScope(double s);
        double          getScope();
        void            setVolume(double v);
        double          getVolume();
        ~Rectangle();
    };

}

#endif // GEOMETRY_H_INCLUDED
