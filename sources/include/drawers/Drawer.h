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

        Canvas<Point2D<int>> & _canvas;

    public:

        Drawer(Canvas<Point2D<int>>& canvas) : _canvas{canvas} {/*empty*/} 

        /**
         * Algorithm to draw the object in the canvas.
         *
         * @param canvas the canvas
         * */
        virtual void draw(const ObjType & obj) const = 0;

};

#endif
