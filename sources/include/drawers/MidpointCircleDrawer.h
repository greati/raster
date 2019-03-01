#ifndef __MIDP_CIRCLE_DRAWER__
#define __MIDP_CIRCLE_DRAWER__

#include "objects/Circle.h"

class MidpointCircleDrawer : public Drawer<Circle<>> {

    public:

        MidpointCircleDrawer(Canvas<Point2D<int>>& canvas) : Drawer{canvas} {/*empty*/}
    
        void draw(const Circle<> & circle) const override {
        
        }


};

#endif
