#ifndef __POINT_SAMPLERS__
#define __POINT_SAMPLERS__

#include "objects/Object.h"
#include "objects/Polygon.h"
#include "common.h"

template<typename PointType = Point2D<int>>
class PointSampler {

    public:

        virtual PointType one(const PointType & obj) = 0;
        virtual std::vector<PointType> many(const PointType & obj) = 0;

};

class DummyPointSampler : public PointSampler<Point2D<int>> {
    public:

        Point2D<int> one(const Point2D<int> & point) override {
            return point;
        }

        std::vector<Point2D<int>> many(const Point2D<int> & point) override {
            return std::vector<Point2D<int>>{point}; 
        }
};

class SquarePointSampler : public PointSampler<Point2D<int>> {

    private:

        Size<2> frame_size;
        int padding;

    public:

        SquarePointSampler(const Size<2> & _frame_size, int _padding = 2) : frame_size {_frame_size}, padding {_padding} {/*empty*/}

        Point2D<int> one(const Point2D<int> & point) override {
            return square_sample(point)[0]; 
        }

        std::vector<Point2D<int>> many(const Point2D<int> & point) override {
            return square_sample(point); 
        }


    private:

        std::vector<Point2D<int>> square_sample(const Point2D<int> & point) {
            auto [x, y] = point;
            auto [width, height] = frame_size;
            std::vector<Point2D<int>> points;

            for (int j = std::max(0, x - padding); j < std::min(x + padding, height); ++j) {
                points.push_back({j, std::max(0, y-padding)});
                points.push_back({j, std::min(width, y+padding)});
            }
            for (int i = std::max(0, y - padding); i < std::min(y + padding, width); ++i) {
                points.push_back({std::max(0, x-padding), y});
                points.push_back({std::min(height, x+padding), y});
            }
            return points;
        }

};

#endif
