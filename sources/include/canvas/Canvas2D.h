#ifndef __CANVAS2D__
#define __CANVAS2D__

#include <memory>
#include "Canvas.h"
#include "common.h"

/**
 * A canvas for drawing 2D scenes.
 *
 * @author Vitor Greati
 */
template<int N>
class Canvas2D : public Canvas<Point2D<int>, N> {

    private:
        int _width;                                  /* Canvas width */
        int _height;                                 /* Canvas height */
        std::unique_ptr<unsigned char[]> _data;        /* Canvas pixels */

    public:
        
        Canvas2D(int width, int height);

        PixelValue<N> at(Point2D<int> point) const override;

        void set(Point2D<int> point, PixelValue<N> value) const override;

        void set(Point2D<int> point, PixelValue<N> value, std::nothrow_t) const noexcept override;

        inline int channels() const noexcept { return N; }

        inline int width() const noexcept override { return _width; }

        inline int height() const noexcept override { return _height; }

        inline unsigned char* data() noexcept { return _data.get(); }

    private:
    
        /**
         * Validates a given point with respect to the width and height range.
         *
         * @param point the point
         * */
        void validate(const Point2D<int> & point) const;
        
        /**
         * Given a point, return its real position inside the data member.
         *
         * @param point the point
         * @return the real position in the data member
         * */
        std::pair<int, int> real_pos(const Point2D<int> & point) const;
        
};

#endif
