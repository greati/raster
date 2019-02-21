#ifndef __LINESEG__
#define __LINESEG__

#include "common.h"

template<typename T=double, typename ColorType = RGBColor>
class LineSegment : public Object {

    private:

        Point2D<T> _p1, _p2;
        ColorType _stroke;
        int _thickness;

    public:

        LineSegment(Point2D<T> p1, Point2D<T> p2, ColorType stroke) 
            : _p1{p1}, _p2{p2}, _stroke{stroke}, _thickness{1} {/*empty*/};

        LineSegment(Point2D<T> p1, Point2D<T> p2, ColorType stroke, int thickness) 
            : _p1{p1}, _p2{p2}, _stroke{stroke}, _thickness{thickness} {/*empty*/};

        std::pair<Point2D<T>, Point2D<T>> get_points() const { return {_p1, _p2}; };

        int thickness() const { return _thickness; } 

        ColorType stroke() const { return _stroke; } 

};

#endif
