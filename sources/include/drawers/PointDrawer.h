#ifndef __POINT_DRAWABLE__
#define __POINT_DRAWABLE__

#include "objects/Point.h"
#include <iostream>

class PointDrawer : Drawer<Point<>> {

    public:

        PointDrawer(Canvas<Point2D<int>>& canvas) : Drawer{canvas} {/*empty*/}

        void draw(const Point<>& point) const {
            auto [px, py] = point.coords();
            auto [r, g, b] = point.color();
            this->_canvas.set({px, py}, {r, g, b});
        };

};

#endif
