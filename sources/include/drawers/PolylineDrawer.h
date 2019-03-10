#ifndef __POLYLINE_DRAWABLE__
#define __POLYLINE_DRAWABLE__

#include "objects/Polyline.h"
#include "objects/LineSegment.h"
#include "drawers/Drawer.h"
#include "drawers/BresenhamLineDrawer.h"
#include "drawers/XiaolinWuLineDrawer.h"
#include "drawers/DDALineDrawer.h"
#include <iostream>

class PolylineDrawer : Drawer<Polyline<>> {

    public:

        PolylineDrawer(Canvas<Point2D<int>>& canvas) : Drawer{canvas} {/*empty*/}

        void draw(const Polyline<>& poly) const {

            //XiaolinWuLineDrawer line_drawer {this->_canvas};
            DDALineDrawer line_drawer {this->_canvas};

            auto [r, g, b] = poly.stroke().value().color;
            auto thickness = poly.stroke().value().thickness;
            auto vertices = poly.vertices();
            for (auto i = 0; i < vertices.size() - 1; ++i) {
                line_drawer.draw(LineSegment<> {vertices[i], vertices[i+1], Object::Stroke<RGBColor>{{r, g, b}, thickness}}); 
            }

        }
};

#endif
