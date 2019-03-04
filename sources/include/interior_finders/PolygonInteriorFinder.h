#ifndef __POLYGONINTERIORFINDER__
#define __POLYGONINTERIORFINDER__

#include "common.h"
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
                        std::cout << p.first << " " << p.second << std::endl;
                        break;
                    }
            }
            return int_points;
        };

    private:

        enum class Orientation {
            COLINEAR,
            CLOCKWISE,
            COUNTER_CLOCKWISE,
        };

        bool is_interior(const Polygon<> & polygon, const Point2D<int> point) const {

            auto [px, py] = point;

            Point2D<int> inf_pt {px, std::numeric_limits<int>::max()};

            //std::cout << do_intersect({5, 30}, {15, 50}, {8, 8}, inf_pt) << std::endl;
            std::cout << do_intersect({10, 10}, {5, 30}, {8, 8}, inf_pt) << std::endl;

            return true;

            auto vertices = polygon.vertices();
            int count = 0;

            for (auto i = 0; i < polygon.vertices().size(); ++i) {
                Point2D<int> p1 = vertices[i];
                Point2D<int> p2 = vertices[(i+1)%polygon.vertices().size()];

                if (do_intersect(p1, p2, point, inf_pt)) {
                    if (orientation(p1, point, p2) == Orientation::COLINEAR) {
                        return on_segment(p1, point, p2);
                    }
                    count++;
                }
            }
            std::cout << count << std::endl;
            return (count % 2 == 1);        
        }

        bool do_intersect(const Point2D<int> & p1, const Point2D<int> & q1, const Point2D<int> & p2, const Point2D<int> & q2) const {

            Orientation o1 = orientation(p1, q1, p2);
            Orientation o2 = orientation(p1, q1, q2);
            Orientation o3 = orientation(p2, q2, p1);
            Orientation o4 = orientation(p2, q2, q1);

            print(o1);
            print(o2);
            print(o3);
            print(o4);

            if (o1 != o2 and o3 != o4)
                return true;

            if (o1 == Orientation::COLINEAR && on_segment(p1, p2, q1)) return true;
            if (o2 == Orientation::COLINEAR && on_segment(p1, q2, q1)) return true;
            if (o3 == Orientation::COLINEAR && on_segment(p2, p1, q2)) return true;
            if (o4 == Orientation::COLINEAR && on_segment(p2, q1, q2)) return true;

            return false;
        
        }

        void print(Orientation o) const {
            switch(o) {
                case Orientation::CLOCKWISE:
                    std::cout << "clockwise\n";
                    break;
                case Orientation::COUNTER_CLOCKWISE:
                    std::cout << "cclockwise\n";
                    break;
                case Orientation::COLINEAR:
                    std::cout << "colinear\n";
                    break;
            }
        }
    
        Orientation orientation(const Point2D<int> & p, const Point2D<int> & q, const Point2D<int> & r) const {
            auto [px, py] = p;
            auto [qx, qy] = q;
            auto [rx, ry] = r;
            int val = (qx - px) * (ry - qy) - (qy - py) * (rx - qx);
            std::cout << "val: " << val << std::endl;
            if (val == 0) return Orientation::COLINEAR;
            else if (val > 0) return Orientation::COUNTER_CLOCKWISE;
            else return Orientation::CLOCKWISE;
        }

        bool on_segment(const Point2D<int> & p, const Point2D<int> & q, const Point2D<int> & r) const {
            auto [px, py] = p;
            auto [qx, qy] = q;
            auto [rx, ry] = r;
            return (qy <= std::max(py, ry) and qy >= std::min(py, ry)
                    and qx <= std::max(px, rx) and qx >= std::min(px, rx)); 
        }

};

#endif
