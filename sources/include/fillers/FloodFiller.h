#ifndef __FLOODFILLER__
#define __FLOODFILLER__

class FloodFiller {

    private:

        Canvas<Point2D<int>> & _canvas;

    public:

        enum class Connectivity {
            CONNECTED4,
            CONNECTED8
        };

        FloodFiller(Canvas<Point2D<int>> & canvas) : _canvas {canvas} {/* empty */}

        void fill(const Object& obj, const RGBColor & fill, const RGBColor & old, Connectivity conn) {
            fill_interior({10, 30}, fill, old, conn);
        }

    private:

        void fill_interior(const Point2D<int> & interior, 
                const RGBColor & fill, const RGBColor & old, Connectivity conn) {

            auto [x, y] = interior;
            if (y < 0 || y >= _canvas.width()) return;
            if (x < 0 || x >= _canvas.height()) return;

            auto [fr, fg, fb] = fill;
            auto [r, g, b] = _canvas.at({x, y});

            if (RGBColor{r, g, b} == old) {
                _canvas.set({x, y}, {fr, fg, fb});
                fill_interior({x+1, y}, fill, old, conn);
                fill_interior({x-1, y}, fill, old, conn);
                fill_interior({x, y+1}, fill, old, conn);
                fill_interior({x, y-1}, fill, old, conn);
                if (conn == Connectivity::CONNECTED8) {
                    fill_interior({x+1, y+1}, fill, old, conn);
                    fill_interior({x-1, y-1}, fill, old, conn);
                    fill_interior({x+1, y-1}, fill, old, conn);
                    fill_interior({x-1, y+1}, fill, old, conn);
                }
            }
            
        }

};

#endif
