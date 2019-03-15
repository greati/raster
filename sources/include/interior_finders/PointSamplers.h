#ifndef __POINT_SAMPLERS__
#define __POINT_SAMPLERS__

#include "objects/Object.h"
#include "objects/Polygon.h"
#include "common.h"
#include <random>

/**
 * Interface for point sampler.
 *
 * @author Vitor Greati
 * */
template<typename PointType = Point2D<int>>
class PointSampler {

    public:

        /**
         * Sample one point.
         *
         * @param obj a base point
         * @return a point
         * */
        virtual PointType one(const PointType & obj) = 0;

        /**
         * Sample a list of points.
         *
         * @param obj a base point
         * @return the list of points
         * */
        virtual std::vector<PointType> many(const PointType & obj) = 0;

        /**
         * Update the sampler internal state.
         * */
        virtual void expand() = 0;

        /**
         * Reset the sampler internal state.
         * */
        virtual void reset() = 0;

        /**
         * Finalize the sampler.
         * */
        virtual bool end() = 0;

};

/**
 * Sampler used only for debugging.
 *
 * @author Vitor Greati
 * */
class DummyPointSampler : public PointSampler<Point2D<int>> {
    public:

        Point2D<int> one(const Point2D<int> & point) override {
            return point;
        }

        std::vector<Point2D<int>> many(const Point2D<int> & point) override {
            return std::vector<Point2D<int>>{point}; 
        }

        void expand() override {
            /* do nothing */
        }

        void reset() override {
            /* do nothing */
        }

        bool end() override {
            /* do nothing */
            return false;
        }
};

/**
 * Sample in squares arount a given point.
 * Maintains the state of the current padding.
 *
 * @author Vitor Greati
 * */
class SquarePointSampler : public PointSampler<Point2D<int>> {

    private:

        Size<2> frame_size; /**< Size of the frame */
        int padding;        /**< Padding of the square */

    public:

        SquarePointSampler(const Size<2> & _frame_size, int _padding = 2) : frame_size {_frame_size}, padding {_padding} {/*empty*/}

        Point2D<int> one(const Point2D<int> & point) override {
            auto square = square_sample(point);
            std::random_device rd; 
            std::mt19937 eng(rd()); 
            std::uniform_int_distribution<> distr(0, square.size());
            return square_sample(point)[distr(eng)]; 
        }

        std::vector<Point2D<int>> many(const Point2D<int> & point) override {
            return square_sample(point); 
        }

        void expand() override {
            padding++;
        }

        void reset() override {
            padding = 2;
        }

        bool end() override {
            return (padding >= frame_size[0] || padding >= frame_size[1]);
        }


    private:

        /**
         * Produces a fence around the starting point, using the
         * current padding state.
         *
         * @point the base point
         * @return a list of points
         * */
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
