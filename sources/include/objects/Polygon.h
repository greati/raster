#ifndef __POLYGON__
#define __POLYGON__

#include <vector>
#include "objects/Polyline.h"

template<typename T=double, typename ColorType = RGBColor>
class Polygon : public Polyline<T, ColorType> {

    public:

        Polygon(std::vector<Point2D<T>> & vertices, ColorType stroke_color) :
            Polyline<T, ColorType>(vertices, stroke_color) {
            this->_vertices.push_back(vertices[0]);
        };

        Polygon(std::vector<Point2D<T>> & vertices, ColorType stroke_color, int thickness) :
            Polyline<T, ColorType>(vertices, stroke_color, thickness) {
            this->_vertices.push_back(vertices[0]);
        };

};

#endif
