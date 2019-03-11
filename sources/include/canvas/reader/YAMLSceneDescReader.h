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
 * Reader for scenes described in YAML.
 * */
class YAMLSceneDescReader : public SceneDescReader {

    private:
       std::unique_ptr<DescVisitor> _visitor;

       std::map<std::string, Object&> objects;

       std::map<std::string, Point<>> points;
       std::map<std::string, Polygon<>> polygons;
       std::map<std::string, Circle<>> circles;
       std::map<std::string, LineSegment<>> line_segments;
       std::map<std::string, Polyline<>> polylines;
       std::map<std::string, Ellipsis<>> ellipsis;

       std::map<std::string, Polygon<>> polygons_scanline;

       std::map<std::string, RGBColor> color_pallete = {
           {"red", {255, 0 ,0}},
           {"green", {0, 255 ,0}},
           {"blue", {0, 0, 255}},
       };
       std::map<std::string, Object::Fill<>> fill_pallete;
       std::map<std::string, Object::Stroke<>> stroke_pallete;

    public:

       YAMLSceneDescReader(std::unique_ptr<DescVisitor> visitor) : _visitor {std::move(visitor)} {}

       void read(const std::string & filename) override;

    protected:

       void process_scene(const YAML::Node & scene_node);
       void process_object(const YAML::Node & obj_node, const std::string & obj_label);
       std::optional<Point2D<double>> find_point(const YAML::Node&);
       std::optional<RGBColor> get_color(const YAML::Node&);
       std::optional<Object::Fill<>> get_fill(const YAML::Node&);
       std::optional<Object::Stroke<>> get_stroke(const YAML::Node&);
};

#endif
