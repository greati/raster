#ifndef __DDALINEDRAWER__
#define __DDALINEDRAWER__

#include "drawers/Drawer.h"
#include "objects/Object.h"
#include "objects/LineSegment.h"

class DDALineDrawer : public Drawer<LineSegment<>> {

    public:

        DDALineDrawer(Canvas<Point2D<int>>& canvas) : Drawer{canvas} {/*empty*/}

        void draw(const LineSegment<> & line) const override {
            /*alg*/
        };

};

#endif
