#ifndef __BRESENHAM_LINE__
#define __BRESENHAM_LINE__

class BresenhamLineDrawer : public Drawer<LineSegment<>> {

    public:

        BresenhamLineDrawer(Canvas<Point2D<int>>& canvas) : Drawer{canvas} {/*empty*/}

        void draw(const LineSegment<> & line) const override {


        
        }
};

#endif
