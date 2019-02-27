#ifndef __POLYLINE__
#define __POLYLINE__

#include <vector>

template<typename T=double, typename ColorType = RGBColor>
class Polyline : public Object {

    private:

        std::vector<Point2D<T>> _vertices;
        ColorType _stroke_color;
        int _thickness;

    public:

        Polyline(std::vector<Point2D<T>> & vertices, ColorType stroke_color) 
            : _vertices {vertices}, _stroke_color{stroke_color}, _thickness{1} {/*empty*/};

        Polyline(std::vector<Point2D<T>> & vertices, ColorType stroke_color, int thickness) 
            : _vertices {vertices}, _stroke_color{stroke_color}, _thickness{thickness} {/*empty*/};

        std::vector<Point2D<T>> vertices() const { return _vertices; };

        int thickness() const { return _thickness; } 

        ColorType stroke_color() const { return _stroke_color; } 



};

#endif
