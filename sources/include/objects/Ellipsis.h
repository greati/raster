#ifndef __ELLIPSIS__
#define __ELLIPSIS__

template<typename T=double, typename ColorType = RGBColor>
class Ellipsis : public Object {

    protected:

        std::pair<double, double> _radius;
        Point2D<T> _center;
        Object::Stroke<ColorType> _stroke;
        std::optional<Object::Fill<ColorType>> _fill;
        std::optional<std::pair<float, float>> _angle_limits;

    public:

        Ellipsis(const Point2D<T> & center, decltype(_radius) radius, Object::Stroke<ColorType> stroke,
                std::optional<Object::Fill<ColorType>> fill = std::nullopt, decltype(_angle_limits) angle_limits = std::nullopt)
            : _center {center}, _radius {radius}, _stroke {stroke}, _fill {fill}, _angle_limits {angle_limits} {/* empty */}

        inline auto radius() const { return _radius; }

        inline Point2D<T> center() const { return _center; }

        inline auto stroke() const { return _stroke; } 

        inline auto fill() const { return _fill; } 

        int max_horizontal() const override {
            return std::max(_radius.first, _radius.second); //TODO improve this for cutted circles
        }

        inline auto angle_limits() const { return _angle_limits; }

};

#endif
