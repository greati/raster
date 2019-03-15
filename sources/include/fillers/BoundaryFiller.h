#ifndef __BOUNDARYFILLER__
#define __BOUNDARYFILLER__

#include "interior_finders/InteriorFinder.h"
#include "interior_finders/PointSamplers.h"
#include "interior_finders/PolygonInteriorFinder.h"
#include "fillers/SingleFiller.h"
#include <vector>
#include <stack>

/**
 * Implement boundary filler algorithm.
 *
 * @author Vitor Greati
 * */
template<typename ObjType>
class BoundaryFiller : public SingleFiller<ObjType> {

    public:

        BoundaryFiller(Canvas<Point2D<int>> & canvas)
            : SingleFiller<ObjType>{canvas} {/* empty */}

        BoundaryFiller(Canvas<Point2D<int>> & canvas, 
                std::shared_ptr<InteriorFinder<ObjType>> interior_finder) 
            : SingleFiller<ObjType>{canvas, interior_finder} {/* empty */}

        void fill(const ObjType& obj, const RGBColor & fill, const RGBColor & border_color, 
                typename SingleFiller<ObjType>::Connectivity conn, 
                std::optional<std::vector<Point2D<int>>> seeds = std::nullopt) {
            if (seeds != std::nullopt) {
                std::for_each(seeds.value().begin(), seeds.value().end(),
                        [&](const Point2D<int> p){
                            fill_interior(p, fill, border_color, conn);
                        });
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

        std::stack<Point2D<int>> points_stack;

        void fill_interior(const Point2D<int> & interior, 
                const RGBColor & fill, const RGBColor & border_color, 
                typename SingleFiller<ObjType>::Connectivity conn) {

            // validation of seed
            auto [r, g, b] = this->_canvas.at(interior);
            auto current = RGBColor{r, g, b};
            if (current == border_color) {
                std::cout << "[warning] boundary filler wont fill: seed color is border color" << std::endl;
                return;
            }
            if (current == fill) {
                std::cout << "[warning] boundary filler wont fill: seed color is fill color" << std::endl;
                return;
            }

            // algorithm goes
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

                if (current != border_color && current != fill) {
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
                            "[warning] boundary filler could not reach an end;"
                            "verify the object's fill and stroke colors";
                    return;
                }
            }

        }

};

#endif

