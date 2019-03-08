
#ifndef __XIAOWU_CIRCLE_DRAWER__
#define __XIAOWU_CIRCLE_DRAWER__

#include "objects/Circle.h"

class XiaolinWuCircleDrawer : public Drawer<Circle<>> {

    public:

        XiaolinWuCircleDrawer(Canvas<Point2D<int>>& canvas) : Drawer{canvas} {/*empty*/}
    
        void draw(const Circle<> & circle) const override {

            auto radius = circle.radius();
            auto [r, g, b] = circle.stroke().color;
            auto [xc, yc] = circle.center();

            int i = 0;
            int j = radius;
            float d = 0.0;
        
            auto dc = [](int r, int i) -> float {
                float x = std::sqrt(r*r - i*i);
                return std::ceil(x) - x;
            };

            draw_symm_points({i, j}, {xc, yc}, {r, g, b});

            while (j > i) {
                i++;
                if (dc(r, i) < d) j--;
                auto [rd, gd, bd] = raster::apply_brightness_rgb({r, g, b}, 1 - dc(r, i));
                auto [ru, gu, bu] = raster::apply_brightness_rgb({r, g, b}, dc(r, i));
                draw_symm_points({i, j}, {xc, yc}, {rd, gd, bd});
                draw_symm_points({i - 1, j}, {xc, yc}, {ru, gu, bu});
                d = dc(r, i); 
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
            this->_canvas.set({xc + y, yc + x}, {r, g, b}, std::nothrow_t {});
            this->_canvas.set({xc - y, yc + x}, {r, g, b}, std::nothrow_t {});
            this->_canvas.set({xc + y, yc - x}, {r, g, b}, std::nothrow_t {});
            this->_canvas.set({xc - y, yc - x}, {r, g, b}, std::nothrow_t {});
        }
};

#endif
