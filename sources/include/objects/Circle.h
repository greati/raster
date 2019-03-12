#ifndef __CIRCLE__
#define __CIRCLE__

#include "objects/Ellipsis.h"

template<typename T=double, typename ColorType = RGBColor>
class Circle : public Ellipsis<T, ColorType> {

    public:

        Circle(const Point2D<T> & center, double radius, Object::Stroke<ColorType> stroke,
                std::optional<Object::Fill<ColorType>> fill, std::optional<std::pair<float, float>> angle_limits = std::nullopt)
            : Ellipsis<T, ColorType>(center, {radius, radius}, stroke, fill, angle_limits) {/* empty */}

        inline double radius() const { return this->_radius.first; }

        int max_horizontal() const override {
            return this->radius(); //TODO improve this for cutted circles
        }

};

#endif
