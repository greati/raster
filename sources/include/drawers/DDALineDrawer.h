#ifndef __DDALINEDRAWER__
#define __DDALINEDRAWER__

#include <cmath>
#include "drawers/Drawer.h"
#include "objects/Object.h"
#include "objects/LineSegment.h"

/**
 * Line drawer based on DDA algorithm.
 * Implements line thickness.
 *
 * @author Vitor Greati
 * */
class DDALineDrawer : public Drawer<LineSegment<>> {

    public:

        DDALineDrawer(Canvas<Point2D<int>>& canvas) : Drawer{canvas} {/*empty*/}

        void draw(const LineSegment<> & line) const override {
            auto [p1, p2] = line.points();
            auto [p1x, p1y] = p1;
            auto [p2x, p2y] = p2;
            double slope = (p2y - p1y) / (p2x - p1x);
            double slope_inv = 1 / slope;
            auto [r, g, b] = line.stroke().color;
            int thickness = line.stroke().thickness;

            // horizontal
            if (p2x - p1x == 0) {
                if (p2y < p1y) std::swap(p1, p2);
                auto [p1x, p1y] = p1;
                auto [p2x, p2y] = p2;
                for (int y = p1y; y <= p2y+thickness-1; ++y) {
                    draw_column(p1x, p1x+thickness-1, y, {r, g, b});
                }             
            }
            //vertical
            else if (p2y - p1y == 0) {
                if (p2x < p1x) std::swap(p1, p2);
                auto [p1x, p1y] = p1;
                auto [p2x, p2y] = p2;
                for (int x = p1x; x <= p2x+thickness-1; ++x) {
                    draw_line(x, p1y, p1y + thickness-1, {r, g, b});
                }
            }
            else if (slope >= -1 and slope <= 1) {

                if (p2x < p1x) std::swap(p1, p2);
                auto [p1x, p1y] = p1;
                auto [p2x, p2y] = p2;

                double y = p1y;
                for (int x = p1x; x <= p2x; ++x) {
                    draw_column(x, x+thickness-1, std::round(y), {r, g, b});
                    y += slope;
                }
            } else {

                if (p2y < p1y) std::swap(p1, p2);
                auto [p1x, p1y] = p1;
                auto [p2x, p2y] = p2;

                double x = p1x;
                for (int y = p1y; y <= p2y; ++y) {
                    draw_line(std::round(x), y, y + thickness-1, {r, g, b});
                    x += slope_inv;
                }             
            }
        };

};

#endif
