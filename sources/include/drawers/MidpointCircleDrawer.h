#ifndef __MIDP_CIRCLE_DRAWER__
#define __MIDP_CIRCLE_DRAWER__

#include "objects/Circle.h"

class MidpointCircleDrawer : public Drawer<Circle<>> {

    public:

        MidpointCircleDrawer(Canvas<Point2D<int>>& canvas) : Drawer{canvas} {/*empty*/}
    
        void draw(const Circle<> & circle) const override {

            auto [xc, yc] = circle.center();
            auto radius = circle.radius();
            auto thickness = circle.stroke().thickness;
            auto color = circle.stroke().color;
            int x = 0;
            int y_outer = radius;
            int p_outer = 1 - y_outer;
            int y_inner = y_outer - thickness + 1;
            int p_inner = 1 - y_inner;

            while (x <= y_outer) {

                draw_column(xc + y_inner, xc + y_outer, yc + x,  color);
                draw_line(xc + x,  yc + y_inner, yc + y_outer, color);
                draw_column(xc - y_outer, xc - y_inner, yc + x,  color);
                draw_line(xc - x,  yc + y_inner, yc + y_outer, color);
                draw_column(xc - y_outer, xc - y_inner, yc - x,  color);
                draw_line(xc - x,  yc - y_outer, yc - y_inner, color);
                draw_column(xc + y_inner, xc + y_outer, yc - x,  color);
                draw_line(xc + x,  yc - y_outer, yc - y_inner, color);

                x++;
                if (p_outer < 0)
                    p_outer += 2 * x + 1;
                else {
                    y_outer--;
                    p_outer += 2 * (x - y_outer + 1);
                }
                //this->draw_symm_points(circle, {x, y});

                if (x > y_inner) {
                    y_inner = x;
                } else {
                    if (p_inner < 0) {
                        p_inner += 2 * x + 1;
                    } else {
                        y_inner--;
                        p_inner += 2 * (x - y_inner + 1);
                    }
                }

            }
        }

    private:

        void draw_line(int x, int y1, int y2, const RGBColor & color) const {
            auto [r, g, b] = color;
            while (y1 <= y2) {
                this->_canvas.set({x, y1}, {r, g, b}, std::nothrow_t {});
                y1++;
            }
        }

        void draw_column(int x1, int x2, int y, const RGBColor & color) const {
            auto [r, g, b] = color;
            while (x1 <= x2) {
                this->_canvas.set({x1, y}, {r, g, b}, std::nothrow_t {});
                x1++;
            }
        }

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
