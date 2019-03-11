#ifndef __DESCVISITOR__
#define __DESCVISITOR__

#include "objects/Point.h"
#include "objects/LineSegment.h"
#include "objects/Polyline.h"
#include "objects/Polygon.h"
#include "objects/Circle.h"
#include "objects/Ellipsis.h"

#include <map>

class DescVisitor {

    public:

        DescVisitor() {/*empty*/};

        ~DescVisitor() {};

        virtual void visit_scene_background(const RGBColor & background) const = 0;

        virtual void visit_scene_background(const std::string & background) const = 0;

        virtual void visit_scene_global_aa(bool aa) = 0;

        virtual void visit_scene_size(const Size<2> &) = 0;

        virtual void visit_object_draw(const Point<> & obj) const = 0;

        virtual void visit_object_draw(const LineSegment<> & obj) = 0;

        virtual void visit_object_draw(const Polyline<> & obj) = 0;

        virtual void visit_object_draw(const Circle<> & obj) const = 0;

        virtual void visit_object_draw(const Polygon<> & obj) = 0;

        virtual void visit_object_draw(const Ellipsis<> & obj) const = 0;

        virtual void visit_scanline_fill(const std::map<std::string, Polygon<>> & objs) = 0;

        virtual void visit_post_processing() = 0;

};

#endif
