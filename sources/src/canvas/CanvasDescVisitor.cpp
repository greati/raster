#include "canvas/CanvasDescVisitor.h"

void CanvasDescVisitor::visit_scene_background(const std::string & background) const {
}

void CanvasDescVisitor::visit_object_draw(const LineSegment<> & obj) const {

    BresenhamLineDrawer bres_drawer {this->_canvas};
    bres_drawer.draw(obj);

}

void CanvasDescVisitor::visit_object_draw(const Point<> & obj) const {

    PointDrawer point_drawer {this->_canvas};
    point_drawer.draw(obj);
}

void CanvasDescVisitor::visit_object_draw(const Polyline<> & obj) const {

    PolylineDrawer poly_drawer {this->_canvas};
    poly_drawer.draw(obj);
}

void CanvasDescVisitor::visit_object_draw(const Polygon<> & obj) const {

    PolylineDrawer poly_drawer {this->_canvas};
    poly_drawer.draw(obj);
}

void CanvasDescVisitor::visit_object_draw(const Circle<> & obj) const {

    MidpointCircleDrawer circle_drawer {this->_canvas};
    circle_drawer.draw(obj);
}

void CanvasDescVisitor::visit_fill(const Object & obj) const {
    //FloodFiller filler {this->_canvas};
    BoundaryFiller filler {this->_canvas};
    filler.fill(obj, {255, 0, 0}, {255, 255, 255}, BoundaryFiller::Connectivity::CONNECTED4);
}

void CanvasDescVisitor::visit_fill(const std::map<std::string, Polygon<>> & objs) const {
    PolygonScanLineFiller filler {this->_canvas};
    filler.fill(objs); 
}
