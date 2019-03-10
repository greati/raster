#include "canvas/CanvasDescVisitor.h"

void CanvasDescVisitor::visit_scene_background(const RGBColor & background) const {
    auto [r, g, b] = background;
    this->_canvas.clear({r, g, b});
}

void CanvasDescVisitor::visit_scene_size(const Size<2> & size) {
    this->_canvas.reset(size);
}

void CanvasDescVisitor::visit_object_draw(const LineSegment<> & obj) {

    auto stroke = obj.stroke();
    auto drawer = get_line_drawer(stroke.drawer);

    if (stroke.thickness == 1 and not stroke.antialiased) {
        if (drawer != nullptr)
            drawer->draw(obj);
    } else if (stroke.thickness == 1 and stroke.antialiased) {
        get_line_drawer(Object::StrokeDrawer::WU)->draw(obj);
    } else if (stroke.thickness > 1 and not stroke.antialiased) {
        get_line_drawer(Object::StrokeDrawer::DDA)->draw(obj);
    } else if (stroke.thickness > 1 and stroke.antialiased) {
        auto wu_drawer = get_line_drawer(Object::StrokeDrawer::WU);
        wu_drawer->draw(obj);
        wu_drawer->draw(obj.parallel(obj.stroke().thickness));
        get_line_drawer(Object::StrokeDrawer::DDA)->draw(obj);
    }
}

void CanvasDescVisitor::visit_object_draw(const Point<> & obj) const {

    PointDrawer point_drawer {this->canvas()};
    point_drawer.draw(obj);
}

void CanvasDescVisitor::visit_object_draw(const Polyline<> & obj) {
    auto vertices = obj.vertices();
    auto stroke = obj.stroke().value();
    for (auto i = 0; i < vertices.size() - 1; ++i) {
        this->visit_object_draw(LineSegment<> {vertices[i], vertices[i+1], stroke}); 
    }
}

void CanvasDescVisitor::visit_object_draw(const Polygon<> & obj) {

    auto vertices = obj.vertices();
    auto fill = obj.fill();
    auto stroke = obj.stroke();

    auto draw_stroke = [&]() {
        for (auto i = 0; i < vertices.size() - 1; ++i) {
            this->visit_object_draw(LineSegment<> {vertices[i], vertices[i+1], stroke.value()}); 
        }
    };

    if (fill != std::nullopt) {
        if (fill.value().filler != Object::Filler::SCANLINE) {
            if (stroke != std::nullopt) {
                draw_stroke();
                get_single_filler(fill.value().filler)->fill(obj, fill.value().color, stroke.value().color,
                        SingleFiller<>::Connectivity::CONNECTED4, fill.value().seed);
            }
        }
    } else {
        draw_stroke();
    }

}

void CanvasDescVisitor::visit_object_draw(const Circle<> & obj) const {

    //XiaolinWuEllipsisDrawer circle_drawer {this->canvas()};
    MidpointCircleDrawer circle_drawer {this->canvas()};
    circle_drawer.draw(obj);
}

void CanvasDescVisitor::visit_object_draw(const Ellipsis<> & obj) const {

    XiaolinWuEllipsisDrawer ellipsis_drawer {this->canvas()};
    ///MidpointCircleDrawer circle_drawer {this->canvas()};
    ellipsis_drawer.draw(obj);
}

void CanvasDescVisitor::visit_scanline_fill(const std::map<std::string, Polygon<>> & objs) {
    PolygonScanLineFiller filler {this->canvas()};
    filler.fill(objs); 

    for (auto [name, pol] : objs) {
        auto vertices = pol.vertices();
        auto stroke = pol.stroke();
        for (auto i = 0; i < vertices.size() - 1; ++i) {
            this->visit_object_draw(LineSegment<> {vertices[i], vertices[i+1], stroke.value()}); 
        }
    }
}

std::unique_ptr<Drawer<LineSegment<>>> CanvasDescVisitor::get_line_drawer(Object::StrokeDrawer drawer) const {
    switch(drawer) {
        case Object::StrokeDrawer::BRESENHAM:
            return std::move(std::make_unique<BresenhamLineDrawer>(this->_canvas));
        case Object::StrokeDrawer::DDA:
            return std::move(std::make_unique<DDALineDrawer>(this->_canvas));
        case Object::StrokeDrawer::WU:
            return std::move(std::make_unique<XiaolinWuLineDrawer>(this->_canvas));
    }
    return nullptr;
}

std::unique_ptr<SingleFiller<Polygon<>>> CanvasDescVisitor::get_single_filler(Object::Filler filler) const {
 
    switch(filler) {
        case Object::Filler::BOUNDARY:
            return std::move(std::make_unique<BoundaryFiller<Polygon<>>>(this->_canvas));
        case Object::Filler::FLOOD:
            return std::move(std::make_unique<FloodFiller<Polygon<>>>(this->_canvas));
    }
    return nullptr;
}

void CanvasDescVisitor::visit_post_processing() {

}
