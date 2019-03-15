#ifndef __POLYSCANLINEFILLER__
#define __POLYSCANLINEFILLER__

#include "canvas/Canvas.h"
#include "objects/Polygon.h"
#include <limits>
#include <cmath>
#include <algorithm>
#include <set>
#include <list>

/**
 * Implementation of scanline algorithm to fill
 * polygons.
 *
 * @author Vitor Greati
 * */
class PolygonScanLineFiller {

    private:

        Canvas<Point2D<int>> & _canvas;

    protected:

        /**
         * Edge representation in the scanline.
         * */
        struct EdgeEntry {
            std::string _obj_name;
            double _inverse_m;
            long _row_max;
            long _row_min;
            double _col_intercept;
            double _delta_row, _delta_col;
            long _slope_int, _slope_frac;
            long _remainder_col = 0;

            EdgeEntry(std::string obj_name, long row_max, long row_min, double col_intercept,
                    double delta_row, double delta_col)
                : _obj_name {obj_name}, _row_max {row_max}, _row_min {row_min}, _col_intercept {col_intercept},
                  _delta_row {delta_row}, _delta_col {delta_col} {
                
                if (_delta_row == 0) _inverse_m = 0.0;
                else _inverse_m = delta_col / delta_row;

            };
        };

    public:

        PolygonScanLineFiller(Canvas<Point2D<int>> & canvas) : _canvas {canvas} {/* empty */}

        /**
         * Fill a list of polygons.
         *
         * @param polygons list of polygons
         * */
        void fill(const std::map<std::string, Polygon<>> & polygons) const {
        
            std::vector<EdgeEntry> general_edges[_canvas.height()];

            // create general table with all vertices (ET), ordered ascending col_intercept
            for (auto & [obj_name, polygon] : polygons) {

                if (polygon.fill() == std::nullopt) continue;

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
                    // ignore horizontal
                    if (std::lround(p2x-p1x) == 0) continue;
                    EdgeEntry edge {
                        obj_name, 
                        max_x,
                        min_x,
                        p1y,
                        p2x-p1x,
                        p2y-p1y
                    };
                    general_edges[min_x].push_back(edge);
                }
            }

            auto sort_inc_rowmax = [](const EdgeEntry & a, const EdgeEntry & b) { 
                return a._row_max < b._row_max;
            };

            auto sort_col_interc = [](const EdgeEntry & a, const EdgeEntry & b) { 
                return a._col_intercept < b._col_intercept;
            };

            // sorting
            for (int i = 0; i < _canvas.height(); ++i) {
                std::sort(general_edges[i].begin(), general_edges[i].end(), sort_col_interc);
            }

            // scanline
            std::vector<EdgeEntry> active_edges;
            int i = 0; // TODO optimization: should be min row
            while (i < _canvas.height()) {
                // new edges
                for (auto & e : general_edges[i])
                   active_edges.push_back(e); 

                std::sort(active_edges.begin(), active_edges.end(), sort_col_interc);

                int j = 0;
                int k = 0, l = 1;
                
                while (true) {

                    if (l >= active_edges.size())
                        break;

                    auto e1 = active_edges[k];
                    auto e2 = active_edges[l]; 

                    if ((i == e1._row_max && i == e2._row_min)) {
                        l++;
                        continue;
                    } else if ((i == e2._row_max && i == e1._row_min)) {
                        k = l;
                        l++;
                        continue;
                    }

                    auto [r, g, b] = polygons.find(e1._obj_name)->second.fill().value().color;
                    for (int x = e1._col_intercept; x <= e2._col_intercept; ++x) {
                        this->_canvas.set({i, x}, {r, g, b}, std::nothrow_t{});
                    }
                    // special: local max or min
                    if (e1._col_intercept == e2._col_intercept) {
                        if ((i == e1._row_min && i == e2._row_min)
                                || (i == e1._row_max && i == e2._row_max)) {
                            k = l;
                            l++;
                            continue;
                        }
                    }
                    l+=2; k+=2;
                }

                // erase row_max edges 
                for (auto it = active_edges.begin(); it != active_edges.end();) {
                    if (it->_row_max == i) {
                        it = active_edges.erase(it);
                    } else it++;
                }
                // next line
                i++;
                // update cols
                for (auto edge = active_edges.begin(); edge != active_edges.end(); ++edge) {
                    if (edge->_delta_row != 0) { // non-horizontal
                        edge->_col_intercept += edge->_inverse_m;
                    }
                
                }
            }

        }

};

#endif
