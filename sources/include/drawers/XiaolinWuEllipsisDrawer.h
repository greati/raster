#ifndef __XIAOWU_ELLIPSIS_DRAWER__
#define __XIAOWU_ELLIPSIS_DRAWER__

#include "objects/Circle.h"

/**
 * Ellipsis drawer based on Xiaoling ellipsis drawer.
 *
 * @author Vitor Greati
 * */
class XiaolinWuEllipsisDrawer : public Drawer<Ellipsis<>> {

    public:

        XiaolinWuEllipsisDrawer(Canvas<Point2D<int>>& canvas) : Drawer{canvas} {/*empty*/}
    
        void draw(const Ellipsis<> & ellipsis) const override {

            auto [rX, rY] = ellipsis.radius();
            auto [r, g, b] = ellipsis.stroke().color;
        
            auto rX2 = rX * rX;
            auto rY2 = rY * rY;

            {
                auto quarter = std::round(rY2 / std::sqrt(rY2 + rX2));

                for (int y = 0; y <= quarter; ++y) {
                    auto x = rX * std::sqrt(1 - y*y/rY2);
                    auto error = x - std::floor(x);

                    auto [rd, gd, bd] = raster::apply_brightness_rgb({r, g, b}, 1 - error);
                    auto [ru, gu, bu] = raster::apply_brightness_rgb({r, g, b}, error);

                    draw_symm_points({std::floor(x), y}, ellipsis.center(), {rd, gd, bd});
                    draw_symm_points({std::floor(x)+1, y}, ellipsis.center(), {ru, gu, bu});
                
                }
            }

            auto quarter = std::round(rX2 / std::sqrt(rY2 + rX2));

            for (int x = 0; x <= quarter; ++x) {
                auto y = rY * std::sqrt(1 - x*x/rX2);
                auto error = y - std::floor(y);

                auto [rd, gd, bd] = raster::apply_brightness_rgb({r, g, b}, 1 - error);
                auto [ru, gu, bu] = raster::apply_brightness_rgb({r, g, b}, error);

                draw_symm_points({x, std::floor(y)}, ellipsis.center(), {rd, gd, bd});
                draw_symm_points({x, std::floor(y)+1}, ellipsis.center(), {ru, gu, bu});
            
            }

        }

    private:

        void draw_symm_points(const Point2D<int> & point, const Point2D<int>& center, const RGBColor & color) const {
            auto [x, y] = point;
            auto [xc, yc] = center;
            auto [r, g, b] = color;
            this->_canvas.set({xc + x, yc + y}, {r, g, b}, std::nothrow_t {});
            this->_canvas.set({xc - x, yc + y}, {r, g, b}, std::nothrow_t {});
            this->_canvas.set({xc + x, yc - y}, {r, g, b}, std::nothrow_t {});
            this->_canvas.set({xc - x, yc - y}, {r, g, b}, std::nothrow_t {});
        }
};

#endif
