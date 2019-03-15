#ifndef __CANVASDESCVISITOR__
#define __CANVASDESCVISITOR__

#include <functional>
#include "utils/imgproc_utils.h"
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

/**
 * A visitor for a 2D canvas based on integer
 * coordinates.
 *
 * @author Vitor Greati
 * */
class CanvasDescVisitor : public DescVisitor {

    private:

        Canvas<Point2D<int>> & _canvas;     /**< Reference to the canvas */

        bool global_aa;                     /**< Indicates global antialiasing */
       
    public:

        /**
         * Constructor which receiver a canvas reference.
         *
         * @param canvas reference to canvas
         * */
        CanvasDescVisitor(Canvas<Point2D<int>> & canvas) : DescVisitor{}, _canvas {canvas} {/*empty*/}

        ~CanvasDescVisitor() {}
        
        /**
         * Reference to the canvas.
         *
         * @return reference to the canvas
         * */
        auto & canvas() const {
            return this->_canvas;
        }

        void visit_scene_background(const RGBColor & background) const override;

        void visit_scene_background(const std::string & filepath) const override;

        void visit_scene_global_aa(bool aa) override;

        void visit_scene_size(const Size<2> &) override;

        void visit_object_draw(const Point<> & obj) const override;

        void visit_object_draw(const LineSegment<> & obj) override;

        void visit_object_draw(const Polyline<> & obj) override;

        void visit_object_draw(const Circle<> & obj) const override;

        void visit_object_draw(const Ellipsis<> & obj) const override;

        void visit_object_draw(const Polygon<> & obj) override;

        void visit_scanline_fill(const std::map<std::string, Polygon<>> & objs) override;

        /**
         * Factory method for ellipsis drawer
         *
         * @param stroke stroke drawer
         * @return pointer to a drawer
         * */
        std::unique_ptr<Drawer<Ellipsis<>>> get_ellipsis_drawer(Object::StrokeDrawer) const;

        /**
         * Factory method for circle drawer
         *
         * @param stroke stroke drawer
         * @return pointer to a drawer
         * */
        std::unique_ptr<Drawer<Circle<>>> get_circle_drawer(Object::StrokeDrawer) const;

        /**
         * Factory method for line segment drawer
         *
         * @param stroke stroke drawer
         * @return pointer to a drawer
         * */
        std::unique_ptr<Drawer<LineSegment<>>> get_line_drawer(Object::StrokeDrawer) const;

        /**
         * Factory method for circle filler.
         *
         * @param filler filler type
         * @return pointer to a filler
         * */
        std::unique_ptr<SingleFiller<Circle<>>> get_single_filler_circle(Object::Filler filler) const;

        /**
         * Factory method for ellipsis filler.
         *
         * @param filler filler type
         * @return pointer to a filler
         * */
        std::unique_ptr<SingleFiller<Ellipsis<>>> get_single_filler_ellipsis(Object::Filler filler) const;

        /**
         * Factory method for polygon filler.
         *
         * @param filler filler type
         * @return pointer to a filler
         * */
        std::unique_ptr<SingleFiller<Polygon<>>> get_single_filler_poly(Object::Filler filler) const;

        void visit_post_processing() override;
};

#endif
