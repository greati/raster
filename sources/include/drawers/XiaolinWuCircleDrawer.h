
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

            auto i = 0;
            auto j = radius;
            float d = 0.0;


        
        }
};

#endif
