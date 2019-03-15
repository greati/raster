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

        Point2D<T> _coords;     /**< Point coordinates */
        ColorType _color;       /**< Point color */

    public:

        Point(Point2D<T> coords) : _coords{coords}, _color{{0, 0, 0}} {/*empty*/} 

        Point(Point2D<T> coords, ColorType color) : _coords{coords}, _color{color} {/*empty*/} 

        /**
         * Point coordinates.
         *
         * @return point coordinates
         * */
        Point2D<T> coords() const { return _coords; }

        /**
         * Color.
         *
         * @return the point color
         * */
        ColorType color() const { return _color; }

        int max_horizontal() const override {
            return _coords.second;
        }


};

#endif
