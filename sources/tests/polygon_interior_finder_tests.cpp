#include "gtest/gtest.h"
#include "interior_finders/PolygonInteriorFinder.h"
#include "interior_finders/PointSamplers.h"
#include "objects/Polygon.h"

class TriangleInteriorFinderTests : public ::testing::Test {

    protected:

        DummyPointSampler point_sampler;
        PolygonInteriorFinder<> interior_finder {point_sampler};

        std::vector<Point2D<double>> points = {{2,1},{1,6},{4,8}};
        Polygon<> polygon { points, Object::Stroke{} };
};

class QuadInteriorFinderTests : public ::testing::Test {

    protected:

        DummyPointSampler point_sampler;
        PolygonInteriorFinder<> interior_finder {point_sampler};

        std::vector<Point2D<double>> points = {{10,10},{5,15},{15,50},{30,1}};
        Polygon<> polygon { points, Object::Stroke{} };
};

TEST_F(QuadInteriorFinderTests, IsNotInteriorCheck_1) {
    ASSERT_FALSE(interior_finder.is_interior(polygon, {3, 17}));
}

TEST_F(TriangleInteriorFinderTests, IsNotInteriorCheck_1) {
    ASSERT_FALSE(interior_finder.is_interior(polygon, {2, 0}));
    ASSERT_FALSE(interior_finder.is_interior(polygon, {1, 6}));
    ASSERT_FALSE(interior_finder.is_interior(polygon, {2, 1}));
    ASSERT_FALSE(interior_finder.is_interior(polygon, {4, 8}));
    ASSERT_FALSE(interior_finder.is_interior(polygon, {2, 8}));
    ASSERT_FALSE(interior_finder.is_interior(polygon, {0, 0}));
}

TEST_F(TriangleInteriorFinderTests, IsInteriorCheck_1) {
    ASSERT_TRUE(interior_finder.is_interior(polygon, {2, 5}));
    ASSERT_TRUE(interior_finder.is_interior(polygon, {2, 4}));
    ASSERT_TRUE(interior_finder.is_interior(polygon, {2, 5}));
}
