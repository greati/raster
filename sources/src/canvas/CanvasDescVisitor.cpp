#include "canvas/CanvasDescVisitor.h"
#include "objects/Point.h"
#include "objects/LineSegment.h"

void CanvasDescVisitor::visit_scene_background(const std::string & background) const {
}

template<>
void CanvasDescVisitor::visit_object(const LineSegment<> & obj) const {
}

template<>
void CanvasDescVisitor::visit_object(const Point<> & obj) const {
}

