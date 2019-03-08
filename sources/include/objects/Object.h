#ifndef __OBJECT__
#define __OBJECT__

#include <string>
#include "common.h"

class Object {

    public:

        enum class Type {
            POINT,
            LINE_SEGMENT,
            CIRCLE,
            POLYLINE,
            POLYGON,
            ELLIPSIS
        };

        template<typename ColorType=RGBColor>
        struct Stroke {
            ColorType color;
            int thickness;

            Stroke() {}

            Stroke(ColorType _color, int _thickness = 1)
                : color {_color}, thickness {_thickness} {/*empty*/}
        };

        template<typename ColorType=RGBColor>
        struct Fill {
            ColorType color;
            Fill() {}
            Fill(ColorType _color) : color {_color} {/*empty*/} 
        };

        std::string name;

        virtual int max_horizontal() const = 0;

};

#endif
