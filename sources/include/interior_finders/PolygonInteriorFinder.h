#ifndef __POLYGONINTERIORFINDER__
#define __POLYGONINTERIORFINDER__

#include "common.h"
#include "InteriorFinder.h"
#include "utils/geometry_utils.h"
#include "PointSamplers.h"
#include <limits>

/**
 * Find point inside polygons.
 * Implements a variation of the parity check internal points.
 *
 * @author Vitor Greati
 * */
template<typename PointType=Point2D<int>>
class PolygonInteriorFinder : public InteriorFinder<Polygon<>, PointType> {

    private:
        PointSampler<> & sampler; /**< A reference to a sampler */

    public:

        PolygonInteriorFinder(PointSampler<> & _sampler) : sampler {_sampler} {/* empty */}

        Point2D<int> find_one(const Polygon<> & polygon) const override {
            auto ps = sampler.many(polygon.vertices()[0]);
            while (!sampler.end()) {
                for (Point2D<int> & p : ps) {
                    if (is_interior(polygon, p)) {
                        sampler.reset();
                        return p;
                    }
                }
                sampler.expand();
                ps = sampler.many(polygon.vertices()[0]);
            }
            sampler.reset();
            return {0, 0};
        };

        std::vector<Point2D<int>> find_many(const Polygon<> & polygon) const override {
            std::vector<Point2D<int>> int_points;
            for (auto v : polygon.vertices()) {
                std::vector<Point2D<int>> ps = sampler.many(v);
                for (auto & p : ps) {
                    if (is_interior(polygon,p)) {
                        int_points.push_back(p);
                        break;
                    }
                }
            }
            return int_points;
        };

        /**
         * Check if a given point is inside a polygon.
         *
         * @param polygon the polygon
         * @param point the point
         * @return if the point is inside
         * */
        bool is_interior(const Polygon<> & polygon, const Point2D<int> point) const {

            auto [px, py] = point;

            Point2D<double> inf_pt {px, polygon.max_horizontal() + 1};

            auto vertices = polygon.vertices();
            int count = 0;

            bool odd = false;

            for (auto i = 0; i < vertices.size() - 1; ++i) {
                Point2D<double> p1 = vertices[i];
                Point2D<double> p2 = vertices[(i + 1) % (vertices.size() - 1)];
                
                if (p1.first < px and p2.first >= px
                        || p2.first < px and p1.first >= px) {
                    if (p1.second + (px-p1.first) / (p2.first - p1.first) * (p2.second - p1.second) < py ) {
                        odd = !odd;
                    } 
                }
                
            }
            return odd;        
        }
};

#endif
