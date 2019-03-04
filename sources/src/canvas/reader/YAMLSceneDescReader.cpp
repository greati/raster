#include <iostream>
#include "canvas/reader/YAMLSceneDescReader.h"
#include "canvas/reader/yaml/YamlCppObjects.h"

void YAMLSceneDescReader::read(const std::string & filename) const {
    
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

}

void YAMLSceneDescReader::process_object(const YAML::Node & obj_node, const std::string & obj_label) const {
    std::string obj_type = obj_node["type"].as<std::string>();

    if (obj_type == "point") {
        auto coords = obj_node["coords"].as<Point2D<double>>();    
        auto color = obj_node["color"].as<RGBColor>();    
        Point p {coords, color};
        this->_visitor->visit_object(p);
    } else if (obj_type == "line") {
        auto start = obj_node["start"].as<Point2D<double>>();    
        auto end = obj_node["end"].as<Point2D<double>>();    
        auto stroke = obj_node["stroke"].as<Object::Stroke<RGBColor>>();
        LineSegment line {start, end, stroke};
        this->_visitor->visit_object(line);
    } else if (obj_type == "polyline" || obj_type == "polygon") {
        auto stroke = obj_node["stroke"] ? std::make_optional(obj_node["stroke"].as<Object::Stroke<RGBColor>>()) : std::nullopt;
        auto node_vertices = obj_node["vertices"];
        std::vector<Point2D<double>> vertices;
        for (auto it = node_vertices.begin(); it != node_vertices.end(); ++it) {
            vertices.push_back(it->as<Point2D<double>>());
        }
        if (obj_type == "polyline") {
            Polyline<> poly {vertices, stroke};
            this->_visitor->visit_object(poly);
        } else if (obj_type == "polygon") {
            auto fill = obj_node["fill"] ? std::make_optional(obj_node["fill"].as<Object::Fill<RGBColor>>()) 
                : std::nullopt;
            Polygon poly {vertices, stroke, fill};
            this->_visitor->visit_fill(std::map<std::string, Polygon<>> {{obj_label, poly}});
            if (stroke != std::nullopt)
                this->_visitor->visit_object(poly);
        }
    } else if (obj_type == "circle") {
        auto stroke = obj_node["stroke"].as<Object::Stroke<RGBColor>>();
        auto radius = obj_node["radius"].as<double>();
        auto center = obj_node["center"].as<Point2D<double>>();
        Circle circle {center, radius, stroke};
        this->_visitor->visit_object(circle);
    } else {
        throw new std::logic_error("invalid object type, " + obj_type);
    }
}
