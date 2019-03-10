#ifndef __CANVASDESCVISITOR__
#define __CANVASDESCVISITOR__

#include <functional>
#include "canvas/reader/DescVisitor.h"
#include "canvas/Canvas.h"
#include "canvas/Canvas2D.h"
#include "objects/Point.h"
#include "objects/LineSegment.h"
#include "objects/Polyline.h"
#include "objects/Circle.h"
#include "objects/Ellipsis.h"
#include "common.h"
#include "drawers/BresenhamLineDrawer.h"
#include "drawers/DDALineDrawer.h"
#include "drawers/XiaolinWuLineDrawer.h"
#include "drawers/PointDrawer.h"
#include "drawers/PolylineDrawer.h"
#include "drawers/MidpointCircleDrawer.h"
#include "drawers/XiaolinWuEllipsisDrawer.h"
#include "fillers/PolygonScanLineFiller.h"
#include "fillers/FloodFiller.h"
#include "fillers/BoundaryFiller.h"
#include "interior_finders/PolygonInteriorFinder.h"
#include <memory>

class CanvasDescVisitor : public DescVisitor {

    private:

        Canvas<Point2D<int>> & _canvas;
       
    public:

        CanvasDescVisitor(Canvas<Point2D<int>> & canvas) : DescVisitor{}, _canvas {canvas} {/*empty*/}

        ~CanvasDescVisitor() {}
        
        auto & canvas() const {
            return this->_canvas;
        }

        void visit_scene_background(const RGBColor & background) const override;

        void visit_scene_size(const Size<2> &) override;

        void visit_object_draw(const Point<> & obj) const override;

        void visit_object_draw(const LineSegment<> & obj) override;

        void visit_object_draw(const Polyline<> & obj) override;

        void visit_object_draw(const Circle<> & obj) const override;

        void visit_object_draw(const Ellipsis<> & obj) const override;

        void visit_object_draw(const Polygon<> & obj) override;

        void visit_scanline_fill(const std::map<std::string, Polygon<>> & objs) override;

        std::unique_ptr<Drawer<Ellipsis<>>> get_ellipsis_drawer(Object::StrokeDrawer) const;

        std::unique_ptr<Drawer<Circle<>>> get_circle_drawer(Object::StrokeDrawer) const;

        std::unique_ptr<Drawer<LineSegment<>>> get_line_drawer(Object::StrokeDrawer) const;

        std::unique_ptr<SingleFiller<Circle<>>> get_single_filler_circle(Object::Filler filler) const;

        std::unique_ptr<SingleFiller<Ellipsis<>>> get_single_filler_ellipsis(Object::Filler filler) const;

        std::unique_ptr<SingleFiller<Polygon<>>> get_single_filler_poly(Object::Filler filler) const;

        void visit_post_processing();
};

#endif
