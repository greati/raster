#include "canvas/CanvasDescVisitor.h"

void CanvasDescVisitor::visit_scene_background(const std::string & background) const {
}

void CanvasDescVisitor::visit_object(const LineSegment<> & obj) const {

    BresenhamLineDrawer bres_drawer {this->_canvas};
    bres_drawer.draw(obj);

}

void CanvasDescVisitor::visit_object(const Point<> & obj) const {

    PointDrawer point_drawer {this->_canvas};
    point_drawer.draw(obj);
}

void CanvasDescVisitor::visit_object(const Polyline<> & obj) const {

    PolylineDrawer poly_drawer {this->_canvas};
    poly_drawer.draw(obj);
}

void CanvasDescVisitor::visit_object(const Polygon<> & obj) const {

    PolylineDrawer poly_drawer {this->_canvas};
    poly_drawer.draw(obj);
}

void CanvasDescVisitor::visit_object(const Circle<> & obj) const {

    MidpointCircleDrawer circle_drawer {this->_canvas};
    circle_drawer.draw(obj);
}

void CanvasDescVisitor::visit_fill(const std::map<std::string, Polygon<>> & objs) const {

}
