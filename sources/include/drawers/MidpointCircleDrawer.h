#ifndef __MIDP_CIRCLE_DRAWER__
#define __MIDP_CIRCLE_DRAWER__

#include "objects/Circle.h"

/**
 * Circle drawer based on midpoint algorithm.
 * Implements line thickness.
 *
 * @author Vitor Greati
 * */
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

            float start_angle = 0.0, end_angle = 360.0;
            if (circle.angle_limits() != std::nullopt) {
                start_angle = circle.angle_limits().value().first; 
                end_angle = circle.angle_limits().value().second; 
            }

            auto angle_between = [start_angle, end_angle](const float& angle) {
                return angle >= start_angle and angle <= end_angle;
            };

            while (x <= y_outer) {
                // discover the angle
                float angle_1 = std::floor(std::acos(static_cast<float>(y_outer)/radius) * (180.0 / M_PI));
                float angle_2 = 90.0 - angle_1; 
                float angle_3 = 90.0 + angle_1; 
                float angle_4 = 180.0 - angle_1;
                float angle_5 = 180.0 + angle_1;
                float angle_6 = 270.0 - angle_1;
                float angle_7 = 270.0 + angle_1;
                float angle_8 = 360.0 - angle_1;

            if (angle_between(angle_2)) {// 2 
                draw_column(xc + y_inner, xc + y_outer, yc + x,  color); // yc+x (1)
            }
            if (angle_between(angle_1)) // 1
                  draw_line(xc + x,  yc + y_inner, yc + y_outer, color); // yc + y_inner
            if (angle_between(angle_7)) // 7
                draw_column(xc - y_outer, xc - y_inner, yc + x,  color); 
            if (angle_between(angle_8)) // 8
                draw_line(xc - x,  yc + y_inner, yc + y_outer, color); // yc + y_inner
            if (angle_between(angle_6)) // 6
                draw_column(xc - y_outer, xc - y_inner, yc - x,  color); // yc-x(2)
            if (angle_between(angle_5)) // 5
                draw_line(xc - x,  yc - y_outer, yc - y_inner, color); // yc - y_outer
            if (angle_between(angle_3)) // 3
                draw_column(xc + y_inner, xc + y_outer, yc - x,  color);
            if (angle_between(angle_4)) // 4
                 draw_line(xc + x,  yc - y_outer, yc - y_inner, color); // yc - y_outer

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
