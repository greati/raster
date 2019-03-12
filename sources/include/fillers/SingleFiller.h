#ifndef __SINGLEFILLER__
#define __SINGLEFILLER__

#include <vector>
#include <optional>
#include "objects/Polygon.h"
#include "interior_finders/InteriorFinder.h"

template<typename ObjType=Polygon<>>
class SingleFiller {

    protected:

        std::shared_ptr<InteriorFinder<ObjType>> _interior_finder;
        Canvas<Point2D<int>> & _canvas;

    public:

        enum class Connectivity {
            CONNECTED4,
            CONNECTED8
        };

        SingleFiller(Canvas<Point2D<int>> & canvas, std::shared_ptr<InteriorFinder<ObjType>> interior_finder) 
            : _canvas {canvas}, _interior_finder {interior_finder} {/* empty */}

        SingleFiller(Canvas<Point2D<int>> & canvas) 
            : _canvas {canvas}, _interior_finder {nullptr} {/* empty */}

        virtual void fill(const ObjType& obj, 
                const RGBColor & fill, 
                const RGBColor & border_color, 
                Connectivity conn,
                std::optional<Point2D<int>> seed = std::nullopt) = 0;

};

#endif

