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

    /**
     * Check segments intersection.
     *
     * @param p1
     * @param q1
     * @param p2
     * @param q2
     * @return if intersect
     * */
    bool do_intersect(
            const Point2D<int> & p1,
            const Point2D<int> & q1,
            const Point2D<int> & p2,
            const Point2D<int> & q2);

    /**
     * Check line orientation.
     *
     * @param p
     * @param q
     * @param r
     * @return the segment orientation
     * */
    SegmentOrientation get_orientation(
            const Point2D<int> & p,
            const Point2D<int> & q,
            const Point2D<int> & r);

    /**
     * Check if point q is on segment pr
     *
     * @param p
     * @param q
     * @param r
     * @return if is on segment
     * */
    bool on_segment(
            const Point2D<int> & p,
            const Point2D<int> & q,
            const Point2D<int> & r);
};

#endif
