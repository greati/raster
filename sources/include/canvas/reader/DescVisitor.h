#ifndef __DESCVISITOR__
#define __DESCVISITOR__

#include "objects/Point.h"
#include "objects/LineSegment.h"

class DescVisitor {

    public:

        virtual void visit_scene_background(const std::string & background) const = 0;

        virtual void visit_object(const Point<> & obj) const = 0;

        virtual void visit_object(const LineSegment<> & obj) const = 0;

};

#endif
