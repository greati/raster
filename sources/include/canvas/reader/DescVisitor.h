#ifndef __DESCVISITOR__
#define __DESCVISITOR__

#include "objects/Point.h"
#include "objects/LineSegment.h"
#include "objects/Polyline.h"
#include "objects/Polygon.h"
#include "objects/Circle.h"

#include <map>

class DescVisitor {

    public:

        DescVisitor() {/*empty*/};

        ~DescVisitor() {};

        virtual void visit_scene_background(const std::string & background) const = 0;

        virtual void visit_object_draw(const Point<> & obj) const = 0;

        virtual void visit_object_draw(const LineSegment<> & obj) const = 0;

        virtual void visit_object_draw(const Polyline<> & obj) const = 0;

        virtual void visit_object_draw(const Circle<> & obj) const = 0;

        virtual void visit_object_draw(const Polygon<> & obj) const = 0;

        virtual void visit_fill(const std::map<std::string, Polygon<>> & objs) const = 0;

        virtual void visit_fill(const Object & obj) const = 0;

};

#endif
