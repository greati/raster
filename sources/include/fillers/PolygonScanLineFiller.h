#ifndef __POLYSCANLINEFILLER__
#define __POLYSCANLINEFILLER__

#include "canvas/Canvas.h"
#include "objects/Polygon.h"

class PolygonScanLineFiller {

    private:

        Canvas<Point2D<int>> _canvas;

    protected:

        struct EdgeEntry {
            std::string obj_name;
            int row_max;
            int col_intercept;
            int delta_row, delta_col;
        };

    public:

        PolygonScanLineFiller(const Canvas<Point2D<int>> & canvas) : _canvas {canvas} {/* empty */}

        void fill(const std::map<std::string, Polygon> & polygons) const {
        
            // create general table with all vertices (ET), ordered ascending col_intercept
            for (auto [obj_name, polygon] : polygons) {
            
            }

        }

};

#endif
