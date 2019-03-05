#ifndef __POLYGONINTERIORFINDER__
#define __POLYGONINTERIORFINDER__

#include "common.h"
#include "InteriorFinder.h"
#include "utils/geometry_utils.h"
#include "PointSamplers.h"
#include <limits>

template<typename PointType=Point2D<int>>
class PolygonInteriorFinder : public InteriorFinder<Polygon<>, PointType> {

    private:
        PointSampler<> & sampler;

    public:

        PolygonInteriorFinder(PointSampler<> & _sampler) : sampler {_sampler} {/* empty */}

        Point2D<int> find_one(const Polygon<> & polygon) const override {
           
            auto p = sampler.one(polygon.vertices()[0]);

            while (not is_interior(polygon, p)) {
                p = sampler.one(polygon.vertices()[0]);
            }
            return p;
        };

        std::vector<Point2D<int>> find_many(const Polygon<> & polygon) const override {
            std::vector<Point2D<int>> int_points;
            for (auto & v : polygon.vertices()) {
                auto ps = sampler.many(v);
                for (auto & p : ps)
                    if (is_interior(polygon,p)) {
                        int_points.push_back(p);
                        break;
                    }
            }
            return int_points;
        };

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
