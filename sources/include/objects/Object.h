#ifndef __OBJECT__
#define __OBJECT__

#include <string>
#include <optional>
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

        enum class StrokeDrawer {
            BRESENHAM,
            DDA,
            WU,
            MIDPOINT
        };

        enum class Filler {
            SCANLINE,
            FLOOD,
            BOUNDARY
        };

        template<typename ColorType=RGBColor>
        struct Stroke {
            ColorType color;
            int thickness {1};
            StrokeDrawer drawer;
            bool antialiased {false};

            Stroke() {}

            Stroke(ColorType _color, int _thickness = 1, StrokeDrawer _drawer = StrokeDrawer::DDA, bool _antialiased = false)
                : color {_color}, thickness {_thickness}, drawer {_drawer}, antialiased {_antialiased} {/*empty*/}
        };

        template<typename ColorType=RGBColor>
        struct Fill {
            ColorType color;
            Filler filler;
            std::optional<Point2D<int>> seed {std::nullopt};

            Fill() {}
            Fill(ColorType _color, Filler _filler = Filler::SCANLINE) : color {_color}, filler {_filler} {/*empty*/} 
        };

        std::string name;

        virtual int max_horizontal() const = 0;

};

#endif
