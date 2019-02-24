#ifndef __BRESENHAM_LINE__
#define __BRESENHAM_LINE__

#include <cmath>

class BresenhamLineDrawer : public Drawer<LineSegment<>> {

    public:

        BresenhamLineDrawer(Canvas<Point2D<int>>& canvas) : Drawer{canvas} {/*empty*/}

        void draw(const LineSegment<> & line) const override {
            auto [p1, p2] = line.points();
            auto [p1x, p1y] = p1;
            auto [p2x, p2y] = p2;
            auto Dx = std::abs(p2x-p1x);
            auto Dy = std::abs(p2y-p1y);
            if (Dx >= Dy) { // 0 < m < 1
                draw_line_low(line, p1x > p2x);
            } else { // m >= 1
                draw_line_high(line, p1y > p2y);
            }
        }

    private:

        void draw_line_low(const LineSegment<> & line, bool reverse) const {
            auto [p1, p2] = line.points();
            if (reverse) std::swap(p1, p2);
            auto [r, g, b] = line.stroke_color();
            auto [p1x, p1y] = p1;
            auto [p2x, p2y] = p2;
            int Dx = p2x - p1x;
            int Dy = p2y - p1y;

            int yinc = 1;
            if (Dy < 0) { // if line is decreasing
                yinc = -1;
                Dy = -Dy;
            }

            int pk = 2 * Dy - Dx;

            this->_canvas.set({p1x, p1y}, {r, g, b});
            int y = p1y;
            for (int x = p1x + 1; x <= p2x; ++x) {
                if (pk < 0)
                    pk = pk + 2 * Dy;
                else {
                    y = y + yinc; 
                    pk = pk + 2 * Dy - 2 * Dx;
                }
                this->_canvas.set({x, y}, {r, g, b});
            }
        }

        void draw_line_high(const LineSegment<> & line, bool reverse) const {
            auto [p1, p2] = line.points();
            if (reverse) std::swap(p1, p2);
            auto [r, g, b] = line.stroke_color();
            auto [p1x, p1y] = p1;
            auto [p2x, p2y] = p2;
            int Dx = p2x - p1x;
            int Dy = p2y - p1y;

            int xinc = 1;
            if (Dx < 0) { // if line is decreasing
                xinc = -1;
                Dx = -Dx;
            }

            int pk = 2 * Dx - Dy;

            this->_canvas.set({p1x, p1y}, {r, g, b});
            std::cout << p1x << " " << p1y << std::endl;
            int x = p1x;
            for (int y = p1y + 1; y <= p2y; ++y) {
                std::cout << pk << std::endl;
                if (pk < 0)
                    pk = pk + 2 * Dx;
                else {
                    x = x + xinc; 
                    pk = pk + 2 * Dx - 2 * Dy;
                }
                this->_canvas.set({x, y}, {r, g, b});
                std::cout << x << " " << y << std::endl;
            }
        }

};

#endif
