#ifndef __BOUNDARYFILLER__
#define __BOUNDARYFILLER__

#include "interior_finders/InteriorFinder.h"
#include "interior_finders/PointSamplers.h"
#include "interior_finders/PolygonInteriorFinder.h"
#include "fillers/SingleFiller.h"
#include <vector>

template<typename ObjType>
class BoundaryFiller : public SingleFiller<ObjType> {

    public:

        BoundaryFiller(Canvas<Point2D<int>> & canvas)
            : SingleFiller<ObjType>{canvas} {/* empty */}

        BoundaryFiller(Canvas<Point2D<int>> & canvas, 
                std::shared_ptr<InteriorFinder<ObjType>> interior_finder) 
            : SingleFiller<ObjType>{canvas, interior_finder} {/* empty */}

        void fill(const ObjType& obj, const RGBColor & fill, const RGBColor & border_color, 
                typename SingleFiller<ObjType>::Connectivity conn, std::optional<Point2D<int>> seed = std::nullopt) {
            if (seed != std::nullopt) {
                fill_interior(seed.value(), fill, border_color, conn);
            } else if (this->_interior_finder != nullptr) {
                std::vector<Point2D<int>> interiors = this->_interior_finder->find_many(obj);
                std::for_each(interiors.begin(), interiors.end(),
                        [&](const Point2D<int>& p) {
                            fill_interior(p, fill, border_color, conn);
                        }
                );
            } else {
                throw new std::logic_error("indicate an interior finder");
            }
        }

    private:

        void fill_interior(const Point2D<int> & interior, 
                const RGBColor & fill, const RGBColor & border_color, 
                typename SingleFiller<ObjType>::Connectivity conn) {

            auto [x, y] = interior;
            if (y < 0 || y >= this->_canvas.width()) return;
            if (x < 0 || x >= this->_canvas.height()) return;

            auto [fr, fg, fb] = fill;
            auto [r, g, b] = this->_canvas.at({x, y});
            auto current = RGBColor{r, g, b};

            if (current != border_color && current != fill) {
                this->_canvas.set({x, y}, {fr, fg, fb});
                fill_interior({x+1, y}, fill, border_color, conn);
                fill_interior({x-1, y}, fill, border_color, conn);
                fill_interior({x, y+1}, fill, border_color, conn);
                fill_interior({x, y-1}, fill, border_color, conn);
                if (conn == SingleFiller<ObjType>::Connectivity::CONNECTED8) {
                    fill_interior({x+1, y+1}, fill, border_color, conn);
                    fill_interior({x-1, y-1}, fill, border_color, conn);
                    fill_interior({x+1, y-1}, fill, border_color, conn);
                    fill_interior({x-1, y+1}, fill, border_color, conn);
                }
            }
            
        }

};

#endif

