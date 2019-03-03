#ifndef __POLYSCANLINEFILLER__
#define __POLYSCANLINEFILLER__

#include "canvas/Canvas.h"
#include "objects/Polygon.h"
#include <limits>
#include <cmath>
#include <algorithm>
#include <set>
#include <list>

class PolygonScanLineFiller {

    private:

        Canvas<Point2D<int>> & _canvas;

    protected:

        struct EdgeEntry {
            std::string _obj_name;
            long _row_max;
            long _col_intercept;
            long _delta_row, _delta_col;
            long _slope_int, _slope_frac;
            long _remainder_col = 0;

            EdgeEntry(std::string obj_name, long row_max, long col_intercept,
                    long delta_row, long delta_col)
                : _obj_name {obj_name}, _row_max {row_max}, _col_intercept {col_intercept},
                  _delta_row {delta_row}, _delta_col {delta_col} {
                
                _slope_int = _delta_col / _delta_row;
                _slope_frac = _delta_col % _delta_row;

            };
        };

    public:

        PolygonScanLineFiller(Canvas<Point2D<int>> & canvas) : _canvas {canvas} {/* empty */}

        void fill(const std::map<std::string, Polygon<>> & polygons) const {
        
            std::vector<EdgeEntry> general_edges[_canvas.height()];

            // create general table with all vertices (ET), ordered ascending col_intercept
            for (auto [obj_name, polygon] : polygons) {
                // collect edges from polygons and annotate important info
                auto vertices = polygon.vertices();
                for (auto i = 0; i < vertices.size() - 1; ++i) {
                    auto [p1x, p1y] = vertices[i];
                    auto [p2x, p2y] = vertices[i + 1];
                    if (p1x > p2x) {
                        std::swap(p1x, p2x);
                        std::swap(p1y, p2y);
                    }
                    auto min_x = std::lround(std::min(p1x, p2x)); // when it has appeared
                    auto max_x = std::lround(std::max(p1x, p2x)); // when will it disappear
                    EdgeEntry edge {
                        obj_name, 
                        max_x,
                        std::lround(p1y),
                        std::lround(p2x-p1x),
                        std::lround(p2y-p1y)
                    };
                    general_edges[min_x].push_back(edge);
                }
            }

            auto sort_inc_rowmax = [](const EdgeEntry & a, const EdgeEntry & b) { 
                return a._row_max < b._row_max;
            };

            // sorting
            for (int i = 0; i < _canvas.height(); ++i) {
                std::sort(general_edges[i].begin(), general_edges[i].end(), sort_inc_rowmax);
                std::cout << i << ":" << std::endl;
                for (auto & e : general_edges[i])
                    std::cout << e._obj_name << " " << e._row_max << " " << e._col_intercept << std::endl;
            }

            // scanline
            std::list<EdgeEntry> active_edges;
            int i = 0; // TODO should be min
            while (i < _canvas.height()) {
                // new edges
                for (auto & e : general_edges[i])
                   active_edges.push_back(e); 
                // fill
                // erase row_max edges 
                for (auto it = active_edges.begin(); it != active_edges.end();) {
                    std::cout << i << " | " << it->_row_max << std::endl;
                    if (it->_row_max == i) {
                        it = active_edges.erase(it);
                    } else it++;
                }
                for (auto e : active_edges) {
                    std::cout << e._obj_name << " " << e._row_max << " " << e._col_intercept << std::endl;
                }
                i++;
                // update
                for (auto edge = active_edges.begin(); edge != active_edges.end(); ++edge) {
                    if (edge->_delta_row != 0) { // non-horizontal
                        if (edge->_delta_row > 0) { // down
                            long add = edge->_slope_int + 
                                ((edge->_remainder_col + edge->_slope_frac) / edge->_delta_row);
                            edge->_remainder_col = (edge->_remainder_col + edge->_slope_frac) % edge->_delta_row;
                            edge->_col_intercept += add;//; 
                        } else { // up
                            long add = std::abs(edge->_slope_int) + 
                                ((edge->_remainder_col + edge->_slope_frac) / std::abs(edge->_delta_row));
                            edge->_remainder_col = (edge->_remainder_col + edge->_slope_frac) % std::abs(edge->_delta_row);
                            edge->_col_intercept -= add;//; 
                        }
                    }
                
                }
            }

        }

};

#endif
