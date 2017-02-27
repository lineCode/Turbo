#ifndef GEOMETRY_H_INCLUDED
#define GEOMETRY_H_INCLUDED

#include "Turbo_constants.h"

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
        const string    TAG = "Point";
        double          x = 0;
        double          y = 0;
        double          z = 0;

    protected:

    public:
        Point();
        Point(Point & p);
        Point(double x);
        Point(double x, double y);
        Point(double x, double y, double z);
        void            add(double x);
        void            add(double x, double y);
        void            add(double x, double y, double z);
        double 		    getX();
        double 		    getY();
        double 		    getZ();
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
        const string    TAG = "Line";
        double          weight = 0;
        Point           p1;
		Point           p2;

    protected:

    public:
        Line();
        Line(Point p1, Point p2);
		Line(double x1, double y1, double x2, double y2);
		double          getWeight();
		double          getLength();
		Point           getFirst();
		Point           getSecond();
        ~Line();
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
		        vector<Point> 	getVertices();
		        vector<Line>    getEdges();
		        Point 			getVertice(Uint16 i);
		        Line 			getEdge(Uint16 i);
        /**
         *
         */
        virtual bool			isEmpty();

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
        virtual double 			getArea() = 0;

        /**
         *
         * Scope of a 2D object is equivalent to the length of its edges
         */
        virtual double 			getScope() = 0;

        /**
         *
         * 2D objects have no volume
         */
        virtual double 			getVolume() = 0;
        ~IShape();
    };


    /**
    *** @class Triangle
    ***
    *** @var
    **/
    class Triangle : protected IShape
    {
    private:
        const string    TAG = "Triangle";
        Point           p1;
		Point           p2;
		Point           p3;

    protected:

    public:
        Triangle();
        Triangle(Triangle & t);
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
    *** @class Rectangle
    ***
    *** @var
    **/
    class Rectangle : protected IShape
    {
    private:
        const string    TAG = "Rectangle";
        Point           p1;
		Point           p2;
		Point           p3;
		Point           p4;

    protected:

    public:
        Rectangle();
        Rectangle(Rectangle & r);
        Rectangle(Point p1, Point p2, Point p3, Point p4);
        Rectangle(double x, double y, double w, double h);
        double          getWidth();
		double          getLength();
		double          getHeight();
        double          getArea();
        double          getScope();
        double          getVolume();
        ~Rectangle();
    };

}

#endif // GEOMETRY_H_INCLUDED
