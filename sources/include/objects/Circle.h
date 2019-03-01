#ifndef __CIRCLE__
#define __CIRCLE__

template<typename T=double, typename ColorType = RGBColor>
class Circle : public Object {

    private:

        double _radius;
        Point2D<T> _center;
        ColorType _stroke_color;

    public:

        Circle(const Point2D<T> & center, double radius, const ColorType & stroke_color)
            : _center {center}, _radius {radius}, _stroke_color {stroke_color} {/* empty */}

        inline double radius() const { return _radius; }

        inline Point2D<T> center() const { return _center; }

        inline ColorType stroke_color() const { return _stroke_color; } 

};

#endif
