#ifndef __CANVASDESCVISITOR__
#define __CANVASDESCVISITOR__

#include "canvas/reader/DescVisitor.h"
#include "canvas/Canvas.h"
#include "objects/Point.h"
#include "objects/LineSegment.h"
#include "objects/Polyline.h"
#include "objects/Circle.h"
#include "objects/Ellipsis.h"
#include "common.h"
#include "drawers/BresenhamLineDrawer.h"
#include "drawers/XiaolinWuLineDrawer.h"
#include "drawers/PointDrawer.h"
#include "drawers/PolylineDrawer.h"
#include "drawers/MidpointCircleDrawer.h"
#include "drawers/XiaolinWuCircleDrawer.h"
#include "drawers/XiaolinWuEllipsisDrawer.h"
#include "fillers/PolygonScanLineFiller.h"
#include "fillers/FloodFiller.h"
#include "fillers/BoundaryFiller.h"
#include "interior_finders/PolygonInteriorFinder.h"

class CanvasDescVisitor : public DescVisitor {

    private:

        Canvas<Point2D<int>> & _canvas;
       
    public:

        CanvasDescVisitor(Canvas<Point2D<int>> & canvas) : DescVisitor{}, _canvas {canvas} {/*empty*/}

        ~CanvasDescVisitor() {}
        
        void visit_scene_background(const std::string & background) const override;

        void visit_object_draw(const Point<> & obj) const override;

        void visit_object_draw(const LineSegment<> & obj) const override;

        void visit_object_draw(const Polyline<> & obj) const override;

        void visit_object_draw(const Circle<> & obj) const override;

        void visit_object_draw(const Ellipsis<> & obj) const override;

        void visit_object_draw(const Polygon<> & obj) const override;

        void visit_fill(const std::map<std::string, Polygon<>> & objs) const override;

        void visit_fill(const Polygon<>& obj) const override;

};

#endif
