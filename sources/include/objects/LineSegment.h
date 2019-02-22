#ifndef __LINESEG__
#define __LINESEG__

#include "common.h"

template<typename T=double, typename ColorType = RGBColor>
class LineSegment : public Object {

    private:

        Point2D<T> _p1, _p2;
        ColorType _stroke_color;
        int _thickness;

    public:

        LineSegment(Point2D<T> p1, Point2D<T> p2, ColorType stroke_color) 
            : _p1{p1}, _p2{p2}, _stroke_color{stroke_color}, _thickness{1} {/*empty*/};

        LineSegment(Point2D<T> p1, Point2D<T> p2, ColorType stroke_color, int thickness) 
            : _p1{p1}, _p2{p2}, _stroke_color{stroke_color}, _thickness{thickness} {/*empty*/};

        std::pair<Point2D<T>, Point2D<T>> points() const { return {_p1, _p2}; };

        int thickness() const { return _thickness; } 

        ColorType stroke_color() const { return _stroke_color; } 

};

#endif
