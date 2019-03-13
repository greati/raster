#ifndef __FLOODFILLER__
#define __FLOODFILLER__

#include "interior_finders/InteriorFinder.h"
#include "fillers/SingleFiller.h"
#include "interior_finders/PointSamplers.h"
#include "interior_finders/PolygonInteriorFinder.h"
#include <stack>

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

        std::stack<Point2D<int>> points_stack;

        void fill_interior(const Point2D<int> & interior, 
                const RGBColor & fill, const RGBColor & old, typename SingleFiller<ObjType>::Connectivity conn) {

            auto [r, g, b] = this->_canvas.at(interior);
            auto current = RGBColor{r, g, b};

            if (current != old) {
                std::cout << "[warning] flood filler wont fill: seed color is not old color" << std::endl;
                return;
            }

            points_stack.push(interior);

            int point_count = 0;

            while (!points_stack.empty()) {
                
                auto [x, y] = points_stack.top();
                points_stack.pop();

                if (y < 0 || y >= this->_canvas.width()) continue;
                if (x < 0 || x >= this->_canvas.height()) continue;

                auto [fr, fg, fb] = fill;
                auto [r, g, b] = this->_canvas.at({x, y});
                auto current = RGBColor{r, g, b};

                if (RGBColor{r, g, b} == old) {
                    this->_canvas.set({x, y}, {fr, fg, fb}, std::nothrow_t{});
                    points_stack.push({x+1, y});
                    points_stack.push({x-1, y});
                    points_stack.push({x, y+1});
                    points_stack.push({x, y-1});
                    if (conn == SingleFiller<ObjType>::Connectivity::CONNECTED8) {
                       points_stack.push({x+1, y+1});
                       points_stack.push({x-1, y-1});
                       points_stack.push({x+1, y-1});
                       points_stack.push({x-1, y+1});
                    }
                }
                
                point_count++;

                if (point_count >= this->_canvas.width() * this->_canvas.height()) {
                    std::cout <<
                            "[warning] flood could not reach an end;"
                            "verify the object's fill and stroke colors" << std::endl;
                    return;
                }
            }
        }

};

#endif
