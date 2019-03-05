#include "gtest/gtest.h"
#include "utils/geometry_utils.h"
#include "common.h"
#include <limits>

TEST(GeometryUtils, IntersectUpwardTests) {
    ASSERT_TRUE(raster::do_intersect({10, 10}, {5, 30}, {8, 8}, {8, 300}));
    ASSERT_FALSE(raster::do_intersect({10, 10}, {5, 30}, {1, 1}, {8, 300}));
    ASSERT_FALSE(raster::do_intersect({10, 10}, {5, 30}, {60, 60}, {8, 300}));
    ASSERT_TRUE(raster::do_intersect({10, 10}, {5, 30}, {8, 8}, {8, 10000000}));
    ASSERT_FALSE(raster::do_intersect({2, 1}, {1, 6}, {0, 1}, {0, 9}));
    ASSERT_TRUE(raster::do_intersect({2, 1}, {1, 6}, {2, 1}, {2, 9}));
}

TEST(GeometryUtils, IntersectDownTests) {
    ASSERT_TRUE(raster::do_intersect({5, 30}, {15, 50}, {8, 8}, {8, 300}));
    ASSERT_FALSE(raster::do_intersect({5, 30}, {15, 50}, {0, 0}, {8, 300}));
    ASSERT_FALSE(raster::do_intersect({5, 30}, {15, 50}, {60, 60}, {8, 300}));
    ASSERT_TRUE(raster::do_intersect({5, 30}, {15, 50}, {8, 8}, {8, 100000000}));
    ASSERT_TRUE(raster::do_intersect({4, 8}, {2, 1}, {3, 2}, {3, 9}));
    ASSERT_FALSE(raster::do_intersect({4, 8}, {2, 1}, {5, 4}, {5, 9}));
    ASSERT_FALSE(raster::do_intersect({2, 1}, {1, 6}, {0, 4}, {0, 9}));
    ASSERT_FALSE(raster::do_intersect({1, 6}, {4, 8}, {0, 4}, {0, 9}));
    ASSERT_FALSE(raster::do_intersect({4, 8}, {2, 1}, {0, 4}, {0, 9}));
}

TEST(GeometryUtils, ColinearOrientationTests) {
    ASSERT_EQ(raster::SegmentOrientation::COLINEAR,
            raster::get_orientation({0, 0},{0, 2},{0, 5}));
    ASSERT_EQ(raster::SegmentOrientation::COLINEAR,
            raster::get_orientation({0, 0},{3, 3},{10, 10}));
    ASSERT_EQ(raster::SegmentOrientation::COLINEAR,
            raster::get_orientation({10, 10},{5, 15},{0, 20}));
}

TEST(GeometryUtils, NonColinearOrientationTests) {
    ASSERT_NE(raster::SegmentOrientation::COLINEAR,
            raster::get_orientation({1, 0},{0, 2},{0, 5}));
    ASSERT_NE(raster::SegmentOrientation::COLINEAR,
            raster::get_orientation({0, 0},{4, 1},{10, 10}));
    ASSERT_NE(raster::SegmentOrientation::COLINEAR,
            raster::get_orientation({10, 10},{5, 15},{0, 21}));
    ASSERT_NE(raster::SegmentOrientation::COLINEAR, raster::get_orientation({2, 1}, {0, 2}, {1, 6}));
    ASSERT_NE(raster::SegmentOrientation::COLINEAR, raster::get_orientation({1, 6}, {0, 2}, {4, 8}));
    ASSERT_NE(raster::SegmentOrientation::COLINEAR, raster::get_orientation({4, 8}, {0, 2}, {2, 1}));
}

TEST(GeometryUtils, OnSegmentTests) {
    ASSERT_TRUE(raster::on_segment({0, 0},{0, 2},{0, 5}));
}
TEST(GeometryUtils, OutSegmentTests) {
    ASSERT_FALSE(raster::on_segment({0, 0},{0, 5},{0, 2}));
}
