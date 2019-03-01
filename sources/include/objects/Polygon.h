#ifndef __POLYGON__
#define __POLYGON__

#include <vector>
#include "objects/Polyline.h"

template<typename T=double, typename ColorType = RGBColor>
class Polygon : public Polyline<T, ColorType> {

    public:

        Polygon(std::vector<Point2D<T>> & vertices, ColorType stroke_color) :
            Polyline<T, ColorType>(vertices, stroke_color) {

            if (vertices[0] != vertices[vertices.size()-1])
                throw std::invalid_argument("last point must match first point to be a polygon");

        };

        Polygon(std::vector<Point2D<T>> & vertices, ColorType stroke_color, int thickness) :
            Polyline<T, ColorType>(vertices, stroke_color, thickness) {
            
            if (vertices[0] != vertices[vertices.size()-1])
                throw std::invalid_argument("last point must match first point to be a polygon");

        };

};

#endif
