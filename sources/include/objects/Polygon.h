#ifndef __POLYGON__
#define __POLYGON__

#include <vector>
#include "objects/Polyline.h"
#include <memory>
#include <optional>

/**
 * Represents a polygon.
 *
 * @author Vitor Greati
 * */
template<typename T=double, typename ColorType = RGBColor>
class Polygon : public Polyline<T, ColorType> {

    private:

        std::optional<Object::Fill<ColorType>> _fill;   /**< Polygon fill */

    public:

        Polygon(std::vector<Point2D<T>> & vertices, std::optional<Object::Stroke<RGBColor>> stroke,
                std::optional<Object::Fill<ColorType>> fill = std::nullopt) :
            Polyline<T, ColorType>(vertices, stroke), _fill {fill} {

            if (stroke == std::nullopt && fill == std::nullopt)
                throw std::invalid_argument("stroke or fill the polygon");

            this->_vertices.push_back(vertices[0]);
        };

        /**
         * The polygon fill.
         *
         * @return the polygon fill
         * */
        auto fill() const { return _fill; }

};

#endif
