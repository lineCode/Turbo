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
         std::string    TAG = "Point";
        double          x = 0;
        double          y = 0;
        double          z = 0;

    protected:

    public:
        Point();
        Point(double x);
        Point(double x, double y);
        Point(double x, double y, double z);
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
		SDL_Point       toSDL_Point();
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
         std::string    TAG = "Line";
        double          weight = 0;
        Point           p1;
		Point           p2;

    protected:

    public:
        Line();

        Line(Point p1, Point p2);
		Line(double x1, double y1, double x2, double y2);
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
         std::string TAG = "Vector";

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
        std::string         TAG = "IShape";
        std::vector<Point>  vertices;
        std::vector<Line>   edges;
        double              width = 0;
        double              length = 0;
        double              height = 0;

    protected:

    public:
        IShape();
                std::vector<Point>      getVertices();
                std::vector<Line>       getEdges();
                Point                   getVertice(Uint16 i);
                Line                    getEdge(Uint16 i);
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
         std::string    TAG = "Triangle";
        Point           p1;
		Point           p2;
		Point           p3;

    protected:

    public:
        Triangle();
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
         std::string    TAG = "Rectangle";
        Point           p1;
		Point           p2;
		Point           p3;
		Point           p4;

    protected:

    public:
        Rectangle();
        Rectangle(Point p1, Point p2, Point p3, Point p4);
        Rectangle(double x, double y, double w, double h);
        void            setX(double x);
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
        SDL_Rect        toSDL_Rect();
        ~Rectangle();
    };

    /*
    *
    *** @class  Cube
    ***
    *** @brief
    **
    class Cube
    {
    private:
        const string TAG = "Cube";

    protected:

    public:
        Cube();
        ~Cube();
    };*/

}

#endif // GEOMETRY_H_INCLUDED
