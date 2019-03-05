#ifndef __BOUNDARYFILLER__
#define __BOUNDARYFILLER__

#include "interior_finders/InteriorFinder.h"
#include <vector>

template<typename ObjType>
class BoundaryFiller {

    private:

        Canvas<Point2D<int>> & _canvas;
        InteriorFinder<ObjType> & _interior_finder;

    public:

        enum class Connectivity {
            CONNECTED4,
            CONNECTED8
        };

        BoundaryFiller(Canvas<Point2D<int>> & canvas, 
                InteriorFinder<ObjType> & interior_finder) 
            : _canvas {canvas}, _interior_finder {interior_finder} {/* empty */}

        void fill(const ObjType& obj, const RGBColor & fill, const RGBColor & border_color, Connectivity conn) {
            std::vector<Point2D<int>> interiors = _interior_finder.find_many(obj);
            std::for_each(interiors.begin(), interiors.end(),
                    [&](const Point2D<int>& p) {
                        std::cout << p.first << " " << p.second << std::endl;
                        fill_interior(p, fill, border_color, conn);
                    }
            );
        }

    private:

        void fill_interior(const Point2D<int> & interior, 
                const RGBColor & fill, const RGBColor & border_color, Connectivity conn) {

            auto [x, y] = interior;
            if (y < 0 || y >= _canvas.width()) return;
            if (x < 0 || x >= _canvas.height()) return;

            auto [fr, fg, fb] = fill;
            auto [r, g, b] = _canvas.at({x, y});
            auto current = RGBColor{r, g, b};

            if (current != border_color && current != fill) {
                _canvas.set({x, y}, {fr, fg, fb});
                fill_interior({x+1, y}, fill, border_color, conn);
                fill_interior({x-1, y}, fill, border_color, conn);
                fill_interior({x, y+1}, fill, border_color, conn);
                fill_interior({x, y-1}, fill, border_color, conn);
                if (conn == Connectivity::CONNECTED8) {
                    fill_interior({x+1, y+1}, fill, border_color, conn);
                    fill_interior({x-1, y-1}, fill, border_color, conn);
                    fill_interior({x+1, y-1}, fill, border_color, conn);
                    fill_interior({x-1, y+1}, fill, border_color, conn);
                }
            }
            
        }

};

#endif

