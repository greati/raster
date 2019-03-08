#include <iostream>
#include "canvas/reader/YAMLSceneDescReader.h"
#include "canvas/reader/yaml/YamlCppObjects.h"

void YAMLSceneDescReader::read(const std::string & filename) {
    
    YAML::Node root_node = YAML::LoadFile(filename);

    if (!root_node["scene"])
        throw new std::logic_error("Parse error: missing scene top level");

    auto scene = root_node["scene"];

    if (scene["background"])
        this->_visitor->visit_scene_background(scene["background"].as<std::string>());

    auto objects = scene["objects"];

    for (auto it = objects.begin(); it != objects.end(); ++it) {
        std::string obj_label = it->first.as<std::string>();
        auto obj_node = it->second;
        this->process_object(obj_node, obj_label);
    }

    std::for_each(
            polygons.begin(),
            polygons.end(), 
            [this](std::pair<std::string, Polygon<>> entry){
                this->_visitor->visit_object_draw(entry.second);         
            }
    );
    
    // JUST TESTING
    //this->_visitor->visit_fill(this->polygons.find("my_poly")->second);

    ///this->_visitor->visit_fill(this->polygons);
}

void YAMLSceneDescReader::process_object(const YAML::Node & obj_node, const std::string & obj_label) {
    Object::Type obj_type = obj_node.as<Object::Type>();

    switch (obj_type) {
        case Object::Type::POINT: {
                auto coords = obj_node["coords"].as<Point2D<double>>();    
                auto color = obj_node["color"].as<RGBColor>();    
                Point<> p {coords, color};
                this->points.insert({obj_label, p});
                this->_visitor->visit_object_draw(p);
                break;
            }
        case Object::Type::LINE_SEGMENT: {
                auto start = obj_node["start"].as<Point2D<double>>();    
                auto end = obj_node["end"].as<Point2D<double>>();    
                auto stroke = obj_node["stroke"].as<Object::Stroke<RGBColor>>();
                LineSegment line {start, end, stroke};
                this->line_segments.insert({obj_label, line});
                this->_visitor->visit_object_draw(line);
                break;
            }
        case Object::Type::CIRCLE: {
                auto stroke = obj_node["stroke"].as<Object::Stroke<RGBColor>>();
                auto radius = obj_node["radius"].as<double>();
                auto center = obj_node["center"].as<Point2D<double>>();
                Circle circle {center, radius, stroke};
                this->circles.insert({obj_label, circle});
                this->_visitor->visit_object_draw(circle);
                break;
            }
        case Object::Type::ELLIPSIS: {
                auto stroke = obj_node["stroke"].as<Object::Stroke<RGBColor>>();
                auto radiusX = obj_node["radius_v"].as<double>();
                auto radiusY = obj_node["radius_h"].as<double>();
                auto center = obj_node["center"].as<Point2D<double>>();
                Ellipsis<> ellipsis {center, {radiusX, radiusY}, stroke};
                this->ellipsis.insert({obj_label, ellipsis});
                this->_visitor->visit_object_draw(ellipsis);
                break;
            }
        case Object::Type::POLYLINE:
        case Object::Type::POLYGON: {
                auto stroke = obj_node["stroke"] 
                    ? std::make_optional(obj_node["stroke"].as<Object::Stroke<RGBColor>>()) 
                    : std::nullopt;
                auto node_vertices = obj_node["vertices"];
                std::vector<Point2D<double>> vertices;
                for (auto it = node_vertices.begin(); it != node_vertices.end(); ++it) {
                    vertices.push_back(it->as<Point2D<double>>());
                }
                if (obj_type == Object::Type::POLYLINE) {
                    Polyline<> poly {vertices, stroke};
                    this->polylines.insert({obj_label, poly});
                    this->_visitor->visit_object_draw(poly);
                } else if (obj_type == Object::Type::POLYGON) {
                    auto fill = obj_node["fill"]
                        ? std::make_optional(obj_node["fill"].as<Object::Fill<RGBColor>>()) 
                        : std::nullopt;
                    Polygon poly {vertices, stroke, fill};
                    this->polygons.insert({obj_label, poly});
                    //if (stroke != std::nullopt)
                    //    this->_visitor->visit_object_draw(poly);
                }
                break;
            }
        default:
            throw new std::logic_error("invalid object type");
    }
}
