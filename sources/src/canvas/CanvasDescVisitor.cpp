#include "canvas/CanvasDescVisitor.h"
#include "lodepng.h"

void CanvasDescVisitor::visit_scene_background(const RGBColor & background) const {
    auto [r, g, b] = background;
    this->_canvas.clear({r, g, b});
}

void CanvasDescVisitor::visit_scene_background(const std::string & filepath) const {
     std::vector<unsigned char> image; //the raw pixels
     unsigned width, height;
     unsigned error = lodepng::decode(image, width, height, filepath);
     if (error) {
         std::cout << "error when loading the background image...";
         return;
     }

     int row, col;
     for (int i = 0; i < width*height*4; i += 4) {
         auto r = image[i]; 
         auto g = image[i + 1]; 
         auto b = image[i + 2];
         row = i / (4*width);
         col = (i/4) - row*width;
         this->_canvas.set({row, col}, {r, g, b}, std::nothrow_t{});
     }
}

void CanvasDescVisitor::visit_scene_global_aa(bool aa) {
    this->global_aa = aa;
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
                if (obj.interior_points() == std::nullopt) {
                    std::cout << "[warning] raster will try to find interior points"  << std::endl;
                }
                get_single_filler_poly(fill.value().filler)->fill(obj, fill.value().color, stroke.value().color,
                        SingleFiller<>::Connectivity::CONNECTED4, obj.interior_points());
            }
        }
    } else {
        draw_stroke();
    }

}

void CanvasDescVisitor::visit_object_draw(const Circle<> & obj) const {
    auto stroke = obj.stroke();
    if (stroke.antialiased) {
        get_ellipsis_drawer(Object::StrokeDrawer::WU)->draw(obj); 
    } else {
        get_circle_drawer(Object::StrokeDrawer::MIDPOINT)->draw(obj); 
    }
    auto fill = obj.fill();
    if (fill != std::nullopt) {
        get_single_filler_circle(fill.value().filler)->
            fill(obj, fill.value().color, stroke.color, 
                    SingleFiller<Circle<>>::Connectivity::CONNECTED4, std::vector<Point2D<int>>{obj.center()}
            );
    }
}

void CanvasDescVisitor::visit_object_draw(const Ellipsis<> & obj) const {
    XiaolinWuEllipsisDrawer ellipsis_drawer {this->canvas()};
    ellipsis_drawer.draw(obj);

    auto stroke = obj.stroke();
    auto fill = obj.fill();
    if (fill != std::nullopt) {
        get_single_filler_ellipsis(fill.value().filler)->
            fill(obj, fill.value().color, stroke.color, 
                    SingleFiller<Ellipsis<>>::Connectivity::CONNECTED4, std::vector<Point2D<int>>{obj.center()}
            );
    }
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

std::unique_ptr<SingleFiller<Ellipsis<>>> CanvasDescVisitor::get_single_filler_ellipsis(Object::Filler filler) const {
    switch(filler) {
        case Object::Filler::BOUNDARY:
            return std::move(std::make_unique<BoundaryFiller<Ellipsis<>>>(this->_canvas));
        case Object::Filler::FLOOD:
            return std::move(std::make_unique<FloodFiller<Ellipsis<>>>(this->_canvas));
    }
    return nullptr;
}

std::unique_ptr<SingleFiller<Circle<>>> CanvasDescVisitor::get_single_filler_circle(Object::Filler filler) const {
 
    switch(filler) {
        case Object::Filler::BOUNDARY:
            return std::move(std::make_unique<BoundaryFiller<Circle<>>>(this->_canvas));
        case Object::Filler::FLOOD:
            return std::move(std::make_unique<FloodFiller<Circle<>>>(this->_canvas));
    }
    return nullptr;
}

std::unique_ptr<SingleFiller<Polygon<>>> CanvasDescVisitor::get_single_filler_poly(Object::Filler filler) const {
 
    SquarePointSampler sampler{{this->_canvas.height(), this->_canvas.width()}};
    auto interior_finder = std::make_shared<PolygonInteriorFinder<>>(sampler);

    switch(filler) {
        case Object::Filler::BOUNDARY:
            return std::move(std::make_unique<BoundaryFiller<Polygon<>>>(this->_canvas, interior_finder));
        case Object::Filler::FLOOD:
            return std::move(std::make_unique<FloodFiller<Polygon<>>>(this->_canvas, interior_finder));
    }
    return nullptr;
}

std::unique_ptr<Drawer<Circle<>>> CanvasDescVisitor::get_circle_drawer(Object::StrokeDrawer drawer) const {
    switch(drawer) {
        case Object::StrokeDrawer::MIDPOINT:
            return std::move(std::make_unique<MidpointCircleDrawer>(this->_canvas));
    }
    return nullptr;

}

std::unique_ptr<Drawer<Ellipsis<>>> CanvasDescVisitor::get_ellipsis_drawer(Object::StrokeDrawer drawer) const {
    switch(drawer) {
        case Object::StrokeDrawer::WU:
            return std::move(std::make_unique<XiaolinWuEllipsisDrawer>(this->_canvas));
    }
    return nullptr;
}

void CanvasDescVisitor::visit_post_processing() {
    if (this->global_aa)
        raster::convolve(this->_canvas, 
                {{1./16, 2./16, 1./16},
                 {2./16, 4./16, 2./16},
                 {1./16, 2./16, 1./16}
                }, {0, 0}, {this->_canvas.height()-1, this->_canvas.width()-1});
}
