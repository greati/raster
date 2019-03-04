#ifndef __POLYLINE__
#define __POLYLINE__

#include <vector>
#include <optional>

template<typename T=double, typename ColorType = RGBColor>
class Polyline : public Object {

    protected:

        std::vector<Point2D<T>> _vertices;
        std::optional<Object::Stroke<ColorType>> _stroke;

    public:

        Polyline(std::vector<Point2D<T>> & vertices, std::optional<Object::Stroke<ColorType>> stroke) 
            : _stroke {stroke} {

            if (vertices.size() < 2) 
                throw std::invalid_argument("provide at least two points for a polyline");
            _vertices = vertices;

        };

        std::vector<Point2D<T>> vertices() const { return _vertices; };

        auto stroke() const { return _stroke; }
};

#endif
