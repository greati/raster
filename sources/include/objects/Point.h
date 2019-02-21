#ifndef __POINT__
#define __POINT__

#include "common.h"
#include "objects/Object.h"

/**
 * Represents a point in the 2D plane.
 *
 * @author Vitor Greati
 * */
template<typename T = double, typename ColorType = RGBColor>
class Point : public Object {

    private:

        Point2D<T> _coords;
        ColorType _color;

    public:

        Point(Point2D<T> coords) : _coords{coords}, _color{{0, 0, 0}} {/*empty*/} 

        Point(Point2D<T> coords, ColorType color) : _coords{coords}, _color{color} {/*empty*/} 

        Point2D<T> coords() const { return _coords; }

        ColorType color() const { return _color; }

};

#endif
