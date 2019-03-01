#ifndef __CIRCLE__
#define __CIRCLE__

template<typename T=double, typename ColorType = RGBColor>
class Circle : public Object {

    private:

        double _radius;
        Point2D<T> _center;
        ColorType _stroke_color;

    public:

        inline double radius() const { return _radius; }

        inline Point2D<T> center() const { return _center; }

        inline ColorType stroke_color() const { return _stroke_color; } 

};

#endif
