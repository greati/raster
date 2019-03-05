#include "utils/geometry_utils.h"

/**
 * Check if segments P1-Q1
 * and P2-Q2 intersect.
 * */
bool raster::do_intersect(
        const Point2D<int> & p1,
        const Point2D<int> & q1,
        const Point2D<int> & p2,
        const Point2D<int> & q2) {

    raster::SegmentOrientation o1 = raster::get_orientation(p1, q1, p2);
    raster::SegmentOrientation o2 = raster::get_orientation(p1, q1, q2);
    raster::SegmentOrientation o3 = raster::get_orientation(p2, q2, p1);
    raster::SegmentOrientation o4 = raster::get_orientation(p2, q2, q1);

    if (o1 != o2 and o3 != o4)
        return true;

    if (o1 == raster::SegmentOrientation::COLINEAR and raster::on_segment(p1, p2, q1)) return true;
    if (o2 == raster::SegmentOrientation::COLINEAR and raster::on_segment(p1, q2, q1)) return true;
    if (o3 == raster::SegmentOrientation::COLINEAR and raster::on_segment(p2, p1, q2)) return true;
    if (o4 == raster::SegmentOrientation::COLINEAR and raster::on_segment(p2, q1, q2)) return true;

    return false;

}

/**
 * Given points p, q, r, determine
 * the orientation of P-Q with respect to Q-R.
 * */
raster::SegmentOrientation raster::get_orientation(
        const Point2D<int> & p,
        const Point2D<int> & q,
        const Point2D<int> & r) {
    auto [px, py] = p;
    auto [qx, qy] = q;
    auto [rx, ry] = r;
    int val = (qx - px) * (ry - qy) - (qy - py) * (rx - qx);
    if (val == 0) return raster::SegmentOrientation::COLINEAR;
    else if (val > 0) return raster::SegmentOrientation::COUNTER_CLOCKWISE;
    else return raster::SegmentOrientation::CLOCKWISE;
}

/**
 * Test if Q is on the segment P-R.
 * */
bool raster::on_segment(
        const Point2D<int> & p,
        const Point2D<int> & q,
        const Point2D<int> & r) {
    auto [px, py] = p;
    auto [qx, qy] = q;
    auto [rx, ry] = r;
    return (qy <= std::max(py, ry) and qy >= std::min(py, ry)
            and qx <= std::max(px, rx) and qx >= std::min(px, rx)); 
}
