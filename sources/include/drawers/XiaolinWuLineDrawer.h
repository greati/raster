#ifndef __XIAOLINWULINEDRAWER__
#define __XIAOLINWULINEDRAWER__

#include "drawers/Drawer.h"
#include "utils/color_utils.h"
#include <iostream>

/**
 * Line drawer with native antialiasing
 * based on "An Efficient Antialiasing Technique",
 * by Xiaolin and Wu.
 *
 * @author Vitor Greati
 * */
class XiaolinWuLineDrawer : public Drawer<LineSegment<>>{

    public:

        XiaolinWuLineDrawer(Canvas<Point2D<int>>& canvas) : Drawer{canvas} {/*empty*/}

        void draw(const LineSegment<> & line) const override {

            auto [x0, y0] = line.points().first;
            auto [x1, y1] = line.points().second;

            auto [r, g, b] = line.stroke().color;

            // define auxiliary lambdas
            auto ipart = [](float x) -> int { return int(std::floor(x)); };
            auto round = [](float x) -> float { return std::round(x); };
            auto fpart = [](float x) -> float { return x - std::floor(x); };
            auto overfpart = [=](float x) -> float { return 1 - fpart(x); };

            const bool steep = std::abs(x1-x0) > std::abs(y1-y0);

            if (steep) {
                std::swap(y0, x0);
                std::swap(y1, x1);
            }

            if (y0 > y1) {
                std::swap(y0, y1); 
                std::swap(x0, x1); 
            }
            
            float k = (y1 - y0) == 0 ? 1 : (x1 - x0) / (y1 - y0); // check for vertical lines

            float D = 0.0;

            // plot first endpoint
            int y0p = 0;
            {
                auto yend = round(y0);              // float
                auto xend = x0 + k * (yend - y0);   // float
                auto ygap = overfpart(y0 + 0.5);    // float to determine the brightness
                y0p = int(yend);                    // int
                auto x0p = ipart(xend);             // int
                auto [ru, gu, bu] = raster::apply_brightness_rgb({r, g, b}, overfpart(xend) * ygap);
                auto [rb, gb, bb] = raster::apply_brightness_rgb({r, g, b}, fpart(xend) * ygap);
                if (!steep) {
                    this->_canvas.set({x0p, y0p}, {ru, gu, bu});
                    this->_canvas.set({x0p + 1, y0p}, {rb, gb, bb});
                } else {
                    this->_canvas.set({y0p, x0p}, {ru, gu, bu});
                    this->_canvas.set({y0p, x0p + 1}, {rb, gb, bb});
                }
                D = xend + k;
            }

            // plot first endpoint
            int y1p = 0;
            {
                auto yend = round(y1);              // float
                auto xend = x1 + k * (yend - y1);   // float
                auto ygap = overfpart(y1 + 0.5);    // float to determine the brightness
                y1p = int(yend);                    // int
                auto x1p = ipart(xend);             // int
                auto [ru, gu, bu] = raster::apply_brightness_rgb({r, g, b}, overfpart(xend) * ygap);
                auto [rb, gb, bb] = raster::apply_brightness_rgb({r, g, b}, fpart(xend) * ygap);
                if (!steep) {
                    this->_canvas.set({x1p, y1p}, {ru, gu, bu});
                    this->_canvas.set({x1p + 1, y1p}, {rb, gb, bb});
                } else {
                    this->_canvas.set({y1p, x1p}, {ru, gu, bu});
                    this->_canvas.set({y1p, x1p + 1}, {rb, gb, bb});
                }
            }
        
            if (!steep) {
                for (int i = y0p + 1; i < y1p; ++i) {
                    auto [ru, gu, bu] = raster::apply_brightness_rgb({r, g, b}, overfpart(D));
                    auto [rb, gb, bb] = raster::apply_brightness_rgb({r, g, b}, fpart(D));
                    this->_canvas.set({ipart(D), i}, {ru, gu, bu});
                    this->_canvas.set({ipart(D) + 1, i}, {rb, gb, bb});
                    D += k;
                }
            } 
            else {
                for (int i = y0p + 1; i < y1p; ++i) {
                    auto [ru, gu, bu] = raster::apply_brightness_rgb({r, g, b}, overfpart(D));
                    auto [rb, gb, bb] = raster::apply_brightness_rgb({r, g, b}, fpart(D));
                    this->_canvas.set({i, ipart(D)}, {ru, gu, bu});
                    this->_canvas.set({i, ipart(D) + 1}, {rb, gb, bb});
                    D += k;
                }
            }
        
        }

};

#endif
