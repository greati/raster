#ifndef __CANVAS2D__
#define __CANVAS2D__

#include <memory>

/**
 * A canvas for drawing 2D scenes.
 *
 * @author Vitor Greati
 */
template<int N>
class Canvas2D {

    private:
        int _width;                                  /* Canvas width */
        int _height;                                 /* Canvas height */
        std::unique_ptr<unsigned char[]> _data;        /* Canvas pixels */

    public:
        
        Canvas2D(int width, int height);

        using Point2D = std::tuple<int, int>;

        using Value = std::array<unsigned char, N>; 

        Value at(Point2D point) const;

        void set(Point2D point, Value value) const;

        inline int channels() const noexcept { return N; }

        inline int width() const noexcept { return _width; }

        inline int height() const noexcept { return _height; }

        inline std::unique_ptr<unsigned char[]> data() noexcept { return std::move(_data); }

    private:
    
        /**
         * Validates a given point with respect to the width and height range.
         *
         * @param point the point
         * */
        void validate(const Point2D & point) const;
        
        /**
         * Given a point, return its real position inside the data member.
         *
         * @param point the point
         * @return the real position in the data member
         * */
        std::pair<int, int> real_pos(const Point2D & point) const;
        
};

#endif
