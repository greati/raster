#ifndef __DDALINEDRAWER__
#define __DDALINEDRAWER__

#include <cmath>
#include "drawers/Drawer.h"
#include "objects/Object.h"
#include "objects/LineSegment.h"

class DDALineDrawer : public Drawer<LineSegment<>> {

    public:

        DDALineDrawer(Canvas<Point2D<int>>& canvas) : Drawer{canvas} {/*empty*/}

        void draw(const LineSegment<> & line) const override {
            auto [p1, p2] = line.points();
            auto [p1x, p1y] = p1;
            auto [p2x, p2y] = p2;
            double slope = (p2y - p1y) / (p2x - p1x);
            double slope_inv = 1 / slope;
            auto [r, g, b] = line.stroke_color();
            int thickness = line.thickness();

            if (slope >= -1 and slope <= 1) {

                if (p2x < p1x) std::swap(p1, p2);
                auto [p1x, p1y] = p1;
                auto [p2x, p2y] = p2;

                double y = p1y;
                for (int x = p1x; x <= p2x; ++x) {
                    this->_canvas.set({x, std::round(y)}, {r, g, b}); 
                    y += slope;
                }

            } else {

                if (p2y < p1y) std::swap(p1, p2);
                auto [p1x, p1y] = p1;
                auto [p2x, p2y] = p2;

                double x = p1x;
                for (int y = p1y; y <= p2y; ++y) {
                    this->_canvas.set({std::round(x), y}, {r, g, b}); 
                    x += slope_inv;
                }             
            }
        };

};

#endif
