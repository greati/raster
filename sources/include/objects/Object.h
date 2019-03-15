#ifndef __OBJECT__
#define __OBJECT__

#include <string>
#include <optional>
#include "common.h"

/**
 * Represents an object in a scene.
 *
 * @author Vitor Greati
 * */
class Object {

    public:

        /**
         * Object types.
         * */
        enum class Type {
            POINT,
            LINE_SEGMENT,
            CIRCLE,
            POLYLINE,
            POLYGON,
            ELLIPSIS
        };

        /**
         * Possible stroke drawers.
         * */
        enum class StrokeDrawer {
            BRESENHAM,
            DDA,
            WU,
            MIDPOINT
        };

        /**
         * Possible fillers.
         * */
        enum class Filler {
            SCANLINE,
            FLOOD,
            BOUNDARY
        };

        /**
         * Represents a stroke.
         * */
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

        /**
         * Represents a fill.
         * */
        template<typename ColorType=RGBColor>
        struct Fill {
            ColorType color;
            Filler filler;
            std::optional<Point2D<int>> seed {std::nullopt};

            Fill() {}
            Fill(ColorType _color, Filler _filler = Filler::SCANLINE) : color {_color}, filler {_filler} {/*empty*/} 
        };

        std::string name;

        /**
         * Maximum horizontal coordinate.
         *
         * @return maximum horizontal coordinate
         * */
        virtual int max_horizontal() const = 0;

};

#endif
