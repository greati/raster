#ifndef __FLOODFILLER__
#define __FLOODFILLER__

#include "interior_finders/InteriorFinder.h"
#include "fillers/SingleFiller.h"
#include "interior_finders/PointSamplers.h"
#include "interior_finders/PolygonInteriorFinder.h"

template<typename ObjType>
class FloodFiller : public SingleFiller<ObjType> {

    public:

        FloodFiller(Canvas<Point2D<int>> & canvas)
            : SingleFiller<ObjType>{canvas} {/* empty */}

        FloodFiller(Canvas<Point2D<int>> & canvas, 
                std::shared_ptr<InteriorFinder<ObjType>> interior_finder) 
            : SingleFiller<ObjType>{canvas, interior_finder} {/* empty */}

        void fill(const ObjType& obj, const RGBColor & fill, const RGBColor & old, 
                typename SingleFiller<ObjType>::Connectivity conn, std::optional<Point2D<int>> seed = std::nullopt) {
            if (seed != std::nullopt) {
                auto [r, g, b] = this->_canvas.at(seed.value());
                fill_interior(seed.value(), fill, {r, g, b}, conn);
            } else if (this->_interior_finder != nullptr) {
                Point2D<int> interior = this->_interior_finder->find_one(obj);
                auto [r, g, b] = this->_canvas.at(interior);
                fill_interior(interior, fill, {r, g, b}, conn);
            } else {
                throw new std::logic_error("indicate an interior finder");
            }
        }

    private:

        void fill_interior(const Point2D<int> & interior, 
                const RGBColor & fill, const RGBColor & old, typename SingleFiller<ObjType>::Connectivity conn) {

            auto [x, y] = interior;
            if (y < 0 || y >= this->_canvas.width()) return;
            if (x < 0 || x >= this->_canvas.height()) return;

            auto [fr, fg, fb] = fill;
            auto [r, g, b] = this->_canvas.at({x, y});

            if (RGBColor{r, g, b} == old) {
                this->_canvas.set({x, y}, {fr, fg, fb}, std::nothrow_t{});
                fill_interior({x+1, y}, fill, old, conn);
                fill_interior({x-1, y}, fill, old, conn);
                fill_interior({x, y+1}, fill, old, conn);
                fill_interior({x, y-1}, fill, old, conn);
                if (conn == SingleFiller<ObjType>::Connectivity::CONNECTED8) {
                    fill_interior({x+1, y+1}, fill, old, conn);
                    fill_interior({x-1, y-1}, fill, old, conn);
                    fill_interior({x+1, y-1}, fill, old, conn);
                    fill_interior({x-1, y+1}, fill, old, conn);
                }
            }
            
        }

};

#endif
