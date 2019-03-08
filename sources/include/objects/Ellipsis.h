#ifndef __ELLIPSIS__
#define __ELLIPSIS__

template<typename T=double, typename ColorType = RGBColor>
class Ellipsis : public Object {

    private:

        std::pair<double, double> _radius;
        Point2D<T> _center;
        Object::Stroke<ColorType> _stroke;

    public:

        Ellipsis(const Point2D<T> & center, decltype(_radius) radius, Object::Stroke<ColorType> stroke)
            : _center {center}, _radius {radius}, _stroke {stroke} {/* empty */}

        inline auto radius() const { return _radius; }

        inline Point2D<T> center() const { return _center; }

        inline auto stroke() const { return _stroke; } 

        int max_horizontal() const override {
            return std::max(_radius.first, _radius.second); //TODO improve this for cutted circles
        }

};

#endif
