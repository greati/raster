#ifndef __CIRCLE__
#define __CIRCLE__

template<typename T=double, typename ColorType = RGBColor>
class Circle : public Object {

    private:

        double _radius;
        Point2D<T> _center;
        Object::Stroke<ColorType> _stroke;

    public:

        Circle(const Point2D<T> & center, double radius, Object::Stroke<ColorType> stroke)
            : _center {center}, _radius {radius}, _stroke {stroke} {/* empty */}

        inline double radius() const { return _radius; }

        inline Point2D<T> center() const { return _center; }

        inline auto stroke() const { return _stroke; } 

        int max_horizontal() const override {
            return _radius; //TODO improve this for cutted circles
        }

};

#endif
