#ifndef __GEOMETRY_UTILS__
#define __GEOMETRY_UTILS__

#include "common.h"

namespace raster {

    /**
     * For a triple of points p, q, r,
     * enumerates the possible orientations.
     * */
    enum class SegmentOrientation {
        COLINEAR,
        CLOCKWISE,
        COUNTER_CLOCKWISE,
    };

    bool do_intersect(
            const Point2D<int> & p1,
            const Point2D<int> & q1,
            const Point2D<int> & p2,
            const Point2D<int> & q2);

    SegmentOrientation get_orientation(
            const Point2D<int> & p,
            const Point2D<int> & q,
            const Point2D<int> & r);

    bool on_segment(
            const Point2D<int> & p,
            const Point2D<int> & q,
            const Point2D<int> & r);
};

#endif
