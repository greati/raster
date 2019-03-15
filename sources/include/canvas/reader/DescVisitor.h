#ifndef __DESCVISITOR__
#define __DESCVISITOR__

#include "objects/Point.h"
#include "objects/LineSegment.h"
#include "objects/Polyline.h"
#include "objects/Polygon.h"
#include "objects/Circle.h"
#include "objects/Ellipsis.h"

#include <map>

/**
 * Visitor class for scene descriptors. 
 *
 * Allows for the independence of parsing and
 * actions over the parsed objects.
 *
 * @author Vitor Greati
 * */
class DescVisitor {

    public:

        DescVisitor() {/*empty*/};

        ~DescVisitor() {};

        /**
         * Called when background color is parsed.
         *
         * @param background background color
         * */
        virtual void visit_scene_background(const RGBColor & background) const = 0;

        /**
         * Called when background url or name is parsed.
         *
         * @param background string representing a name or an url
         * */
        virtual void visit_scene_background(const std::string & background) const = 0;

        /**
         * Called when global antialiasing is parsed.
         *
         * @param aa antialiasing enabled
         * */
        virtual void visit_scene_global_aa(bool aa) = 0;

        /**
         * Called when scene size is parsed.
         *
         * @param size scene size
         * */
        virtual void visit_scene_size(const Size<2> & size) = 0;

        /**
         * Called when a point is parsed.
         *
         * @param point the parsed point
         * */
        virtual void visit_object_draw(const Point<> & point) const = 0;

        /**
         * Called when a line segment is parsed.
         *
         * @param line the parsed line
         * */
        virtual void visit_object_draw(const LineSegment<> & line) = 0;

        /**
         * Called when a polyline is parsed.
         *
         * @param polyline the parsed polyline
         * */
        virtual void visit_object_draw(const Polyline<> & polyline) = 0;

        /**
         * Called when a circle is parsed.
         *
         * @param circle the parsed circle
         * */
        virtual void visit_object_draw(const Circle<> & circle) const = 0;

        /**
         * Called when a polygon is parsed.
         *
         * @param polygon the parsed polygon
         * */
        virtual void visit_object_draw(const Polygon<> & polygon) = 0;

        /**
         * Called when an ellipsis is parsed.
         *
         * @param ellipse the parsed ellipse
         * */
        virtual void visit_object_draw(const Ellipsis<> & ellipse) const = 0;

        /**
         * Called to perform polygon scanline fill.
         *
         * @param polygons the parsed polygons to be scanline filled
         * */
        virtual void visit_scanline_fill(const std::map<std::string, Polygon<>> & polygons) = 0;

        /**
         * Perform post processing.
         * */
        virtual void visit_post_processing() = 0;

};

#endif
