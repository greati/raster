#ifndef __MIDP_CIRCLE_DRAWER__
#define __MIDP_CIRCLE_DRAWER__

#include "objects/Circle.h"

class MidpointCircleDrawer : public Drawer<Circle<>> {

    public:

        MidpointCircleDrawer(Canvas<Point2D<int>>& canvas) : Drawer{canvas} {/*empty*/}
    
        void draw(const Circle<> & circle) const override {

            auto [xc, yc] = circle.center();
            auto radius = circle.radius();
            int x = 0;
            int y = radius;
            int p = 1 - radius;

            this->draw_symm_points(circle, {x, y});

            while (x < y) {
                x++;
                if (p < 0)
                    p += 2 * x + 1;
                else {
                    y--;
                    p += 2 * (x - y) + 1;
                }
                this->draw_symm_points(circle, {x, y});
            }
        }

    private:

        void draw_symm_points(const Circle<> & circle, const Point2D<int> & point) const {
            auto [xc, yc] = circle.center();
            auto [r, g, b] = circle.stroke().color;
            auto [x, y] = point;
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
