#ifndef __ELLIPSIS__
#define __ELLIPSIS__

/**
 * Represents an ellipse.
 *
 * @author Vitor Greati
 * */
template<typename T=double, typename ColorType = RGBColor>
class Ellipsis : public Object {

    protected:

        std::pair<double, double> _radius;                      /**< vertical and horizontal radii */
        Point2D<T> _center;                                     /**< the center */
        Object::Stroke<ColorType> _stroke;                      /**< stroke */
        std::optional<Object::Fill<ColorType>> _fill;           /**< fill */
        std::optional<std::pair<float, float>> _angle_limits;   /**< angle limits to draw arcs */

    public:

        Ellipsis(const Point2D<T> & center, decltype(_radius) radius, Object::Stroke<ColorType> stroke,
                std::optional<Object::Fill<ColorType>> fill = std::nullopt, decltype(_angle_limits) angle_limits = std::nullopt)
            : _center {center}, _radius {radius}, _stroke {stroke}, _fill {fill}, _angle_limits {angle_limits} {/* empty */}

        /**
         * Return the radius
         *
         * @return radius
         */
        inline auto radius() const { return _radius; }

        /**
         * Return the center
         *
         * @return the center
         */
        inline Point2D<T> center() const { return _center; }

        /**
         * Return the stroke
         *
         * @return the stroke
         */
        inline auto stroke() const { return _stroke; } 

        /**
         * Return the fill
         *
         * @return the fill
         */
        inline auto fill() const { return _fill; } 

        /**
         * Return the max horizontal value
         *
         * @return the max horizontal value
         */
        int max_horizontal() const override {
            return std::max(_radius.first, _radius.second); //TODO improve this for cutted circles
        }

        /**
         * Return the angle limits
         *
         * @return the angle limits
         */
        inline auto angle_limits() const { return _angle_limits; }

};

#endif
