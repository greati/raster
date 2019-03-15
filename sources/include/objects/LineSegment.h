#ifndef __LINESEG__
#define __LINESEG__

#include "common.h"

/**
 * Represents a line segment.
 *
 * @author Vitor Greati
 * */
template<typename T=double, typename ColorType = RGBColor>
class LineSegment : public Object {

    private:

        Point2D<T> _p1, _p2;                /**< line start and end points*/
        Object::Stroke<ColorType> _stroke;  /**< stroke */

    public:

        LineSegment(Point2D<T> p1, Point2D<T> p2, const Object::Stroke<ColorType> & stroke) 
            : _p1{p1}, _p2{p2}, _stroke {stroke} {/*empty*/};

        std::pair<Point2D<T>, Point2D<T>> points() const { return {_p1, _p2}; };
        
        Object::Stroke<ColorType> stroke() const { return _stroke; }

        int max_horizontal() const override {
            return std::max(_p1.second, _p2.second);
        }

        /**
         * Produce a thinner line segment.
         *
         * @param delta_thickness thickness variation
         * @return a thinner line segment
         * */
        LineSegment<T, ColorType> thinner(int delta_thickness) const {
            auto stroke = this->_stroke;
            stroke.thickness -= delta_thickness;
            return LineSegment<T, ColorType> {this->_p1, this->_p2, stroke};
        }

        /**
         * Produce a parallel line based on a padding.
         *
         * @param move the padding
         * @return a new line segment parallel to this one
         * */
        LineSegment<T, ColorType> parallel(int move) const {
            auto p1 = this->_p1;
            auto p2 = this->_p2;
            auto [p1x, p1y] = this->_p1;
            auto [p2x, p2y] = this->_p2;
            auto dx = std::abs(p1x-p2x);
            auto dy = std::abs(p1y-p2y);
            auto thickness = this->_stroke.thickness;
            bool steep = dx != 0 && dy != 0 && dx > dy;
            if (dx == 0 || steep) {
                if (p2y < p1y) std::swap(p1, p2);
                auto [p1x, p1y] = p1;
                auto [p2x, p2y] = p2;
                return LineSegment<T, ColorType> {{p1x+thickness-1, p1y},{p2x+thickness-1, p2y}, this->_stroke};
            } else {
                if (p2x < p1x) std::swap(p1, p2);
                auto [p1x, p1y] = p1;
                auto [p2x, p2y] = p2;
                return LineSegment<T, ColorType> {{p1x, p1y+thickness-1},{p2x, p2y+thickness-1}, this->_stroke};
            }
        } 

};

#endif
