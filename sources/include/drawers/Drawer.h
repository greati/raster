#ifndef __DRAWABLE__
#define __DRAWABLE__

#include "canvas/Canvas.h"

/**
 * An interface for drawable objects in the canvas.
 *
 * @author Vitor Greati
 */
template<typename ObjType>
class Drawer {

    protected:

        Canvas<Point2D<int>> & _canvas;     /**< Reference to a 2D canvas */

    public:

        /** 
         * Constructor which takes a canvas reference.
         *
         * @param canvas canvas reference
         * */
        Drawer(Canvas<Point2D<int>>& canvas) : _canvas{canvas} {/*empty*/} 

        /**
         * Algorithm to draw the object in the canvas.
         *
         * @param canvas the canvas
         * */
        virtual void draw(const ObjType & obj) const = 0;

    protected:

        /**
         * Draw a straight line in the canvas.
         *
         * @param x         line index
         * @param y1        col index start
         * @param y2        col index end
         * @param color     color
         * */
        void draw_line(int x, int y1, int y2, const RGBColor & color) const {
            auto [r, g, b] = color;
            while (y1 <= y2) {
                this->_canvas.set({x, y1}, {r, g, b}, std::nothrow_t {});
                y1++;
            }
        }

        /**
         * Draw a straight column in the canvas.
         *
         * @param x1         col index
         * @param x2         row index start
         * @param y          row index end
         * @param color      color
         * */
        void draw_column(int x1, int x2, int y, const RGBColor & color) const {
            auto [r, g, b] = color;
            while (x1 <= x2) {
                this->_canvas.set({x1, y}, {r, g, b}, std::nothrow_t {});
                x1++;
            }
        }
};

#endif
