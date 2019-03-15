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
        std::optional<std::vector<Point2D<int>>> _interior_points {std::nullopt}; /**< interior points */

    public:

        Polygon(std::vector<Point2D<T>> & vertices, std::optional<Object::Stroke<RGBColor>> stroke,
                std::optional<Object::Fill<ColorType>> fill = std::nullopt,
                std::optional<std::vector<Point2D<int>>> inteior_points = std::nullopt) :
            Polyline<T, ColorType>(vertices, stroke), _fill {fill}, _interior_points {inteior_points} {

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

        /**
         * Interior points.
         *
         * @return interior points
         * */
        auto interior_points() const { return _interior_points; }

};

#endif
