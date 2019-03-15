#ifndef __YAMLSCENEREADER__
#define __YAMLSCENEREADER__

#include <string>
#include "canvas/reader/SceneDescReader.h"
#include "canvas/reader/DescVisitor.h"
#include <memory>
#include "yaml-cpp/yaml.h"
#include "common.h"
#include "yaml/YamlCppObjects.h"
#include "objects/Polygon.h"
#include "objects/Ellipsis.h"
#include <algorithm>

/**
 * Reader (parser) for scenes described in YAML.
 *
 * After an object or attribute is parsed, 
 * it is passed to a visitor, which is given by 
 * reference.
 *
 * @author Vitor Greati
 * */
class YAMLSceneDescReader : public SceneDescReader {

    private:
       std::unique_ptr<DescVisitor> _visitor;               /**< A reference to the description visitor */

       std::map<std::string, Point<>> points;               /**< Parsed points */
       std::map<std::string, Polygon<>> polygons;           /**< Parsed polygons */
       std::map<std::string, Circle<>> circles;             /**< Parsed circles */
       std::map<std::string, LineSegment<>> line_segments;  /**< Parsed line segments */
       std::map<std::string, Polyline<>> polylines;         /**< Parsed polylines */
       std::map<std::string, Ellipsis<>> ellipsis;          /**< Parsed ellipsis */

       std::map<std::string, Polygon<>> polygons_scanline;  /**< Polygons to be filled by scanline */

    public:

       /**
        * Constructor with a reference to the visitor instance.
        *
        * @param visitor the visitor of this parser
        * */
       YAMLSceneDescReader(std::unique_ptr<DescVisitor> visitor) : _visitor {std::move(visitor)} {}

       /**
        * Parse an YAML file, calling the visitor methods when appropriate.
        *
        * @param filename path to the YAML file
        * */
       void read(const std::string & filename) override;

    protected:

       /**
        * Process the scene.
        *
        * @param scene_node the scene node
        * */
       void process_scene(const YAML::Node & scene_node);

       /**
        * Process an object.
        *
        * @param obj_node the object node
        * @param obj_label the object label
        * */
       void process_object(const YAML::Node & obj_node, const std::string & obj_label);

       /**
        * Parse a point or search it in the points map.
        *
        * @param point_node the point node
        * */
       std::optional<Point2D<double>> find_point(const YAML::Node& point_node);

       /**
        * Parse a color or search it in the color pallet.
        *
        * @param color_node the color node
        * */
       std::optional<RGBColor> get_color(const YAML::Node& color_node);

       /**
        * Parse a fill or search it in the fill pallet.
        *
        * @param fill_node the fill node
        * */
       std::optional<Object::Fill<>> get_fill(const YAML::Node& fill_node);

       /**
        * Parse a stroke or search it in the stroke pallet.
        *
        * @param stroke_node the stroke node
        * */
       std::optional<Object::Stroke<>> get_stroke(const YAML::Node& stroke_node);


       /**
        * Force a node to be provided, and throws an error otherwise.
        *
        * @param node the node
        * @param nome_name the node name
        * */
       void assert_node(const YAML::Node & node, const std::string& node_name) const {
           if (!node) throw std::logic_error("missing " + node_name);
       }
};

#endif
