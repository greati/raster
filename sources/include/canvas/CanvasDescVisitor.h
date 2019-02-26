#ifndef __CANVASDESCVISITOR__
#define __CANVASDESCVISITOR__

#include "canvas/reader/DescVisitor.h"
#include "canvas/Canvas.h"
#include "objects/Point.h"
#include "objects/LineSegment.h"
#include "common.h"

class CanvasDescVisitor : public DescVisitor {

    private:

        Canvas<Point2D<int>> & _canvas;
       
    public:

        CanvasDescVisitor(Canvas<Point2D<int>> & canvas) : DescVisitor{}, _canvas {canvas} {/*empty*/}

        ~CanvasDescVisitor() {}
        
        void visit_scene_background(const std::string & background) const override;

        void visit_object(const Point<> & obj) const override;

        void visit_object(const LineSegment<> & obj) const override;

};

#endif
