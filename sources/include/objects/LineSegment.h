#ifndef __LINESEG__
#define __LINESEG__

#include "common.h"

template<typename T=double, typename ColorType = RGBColor>
class LineSegment : public Object {

    private:

        Point2D<T> _p1, _p2;
        Object::Stroke<ColorType> _stroke;

    public:

        LineSegment(Point2D<T> p1, Point2D<T> p2, const Object::Stroke<ColorType> & stroke) 
            : _p1{p1}, _p2{p2}, _stroke {stroke} {/*empty*/};

        std::pair<Point2D<T>, Point2D<T>> points() const { return {_p1, _p2}; };
        
        Object::Stroke<ColorType> stroke() const { return _stroke; }

        int max_horizontal() const override {
            return std::max(_p1.second, _p2.second);
        }

};

#endif
