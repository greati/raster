#include <iostream>
#include "canvas/reader/YAMLSceneDescReader.h"
#include "canvas/reader/yaml/YamlCppObjects.h"

void YAMLSceneDescReader::read(const std::string & filename) {
    
    YAML::Node root_node = YAML::LoadFile(filename);

    if (!root_node["scene"])
        throw new std::logic_error("Parse error: missing scene top level");

    auto scene = root_node["scene"];

    if (scene["width"] && scene["height"]) {
        this->_visitor->visit_scene_size(Size<2>{scene["height"].as<int>(), scene["width"].as<int>()});
    } else throw std::logic_error("provide the scene size in terms of height and width");

    if (scene["background"]) {
        this->_visitor->visit_scene_background(scene["background"].as<RGBColor>());
    } else throw std::logic_error("provide a background color for the scene");

    if (scene["global_aa"]) {
        this->_visitor->visit_scene_global_aa(scene["global_aa"].as<bool>()); 
    }

    if (scene["points"]) {
        auto points = scene["points"];
        for (auto it = points.begin(); it != points.end(); ++it) {
            auto label = it->first.as<std::string>();
            auto coords = it->second.as<Point2D<double>>();
            Point<> p {coords, {0, 0, 0}};
            this->points.insert({label, p});
        }
    }

    auto objects = scene["objects"];

    for (auto it = objects.begin(); it != objects.end(); ++it) {
        std::string obj_label = it->first.as<std::string>();
        auto obj_node = it->second;
        this->process_object(obj_node, obj_label);
    }

    this->_visitor->visit_scanline_fill(polygons_scanline);

    this->_visitor->visit_post_processing();

}

void YAMLSceneDescReader::process_object(const YAML::Node & obj_node, const std::string & obj_label) {
    
    if (!obj_node["type"])
        throw std::logic_error("every object must have a type");

    Object::Type obj_type = obj_node["type"].as<Object::Type>();

    switch (obj_type) {
        case Object::Type::POINT: {
                auto coords = find_point(obj_node["coords"]).value();//obj_node["coords"].as<Point2D<double>>();    
                auto color = obj_node["color"].as<RGBColor>();    
                Point<> p {coords, color};
                this->points.insert({obj_label, p});
                this->_visitor->visit_object_draw(p);
                break;
            }
        case Object::Type::LINE_SEGMENT: {
                Point2D<double> start = find_point(obj_node["start"]).value();
                Point2D<double> end = find_point(obj_node["end"]).value();
                auto stroke = obj_node["stroke"].as<Object::Stroke<RGBColor>>();
                LineSegment line {start, end, stroke};
                this->line_segments.insert({obj_label, line});
                this->_visitor->visit_object_draw(line);
                break;
            }
        case Object::Type::CIRCLE: {
                auto stroke = obj_node["stroke"].as<Object::Stroke<RGBColor>>();
                auto radius = obj_node["radius"].as<double>();
                auto center = find_point(obj_node["center"]).value();//obj_node["center"].as<Point2D<double>>();
                auto fill = obj_node["fill"]
                    ? std::make_optional(obj_node["fill"].as<Object::Fill<RGBColor>>()) 
                    : std::nullopt;
                Circle circle {center, radius, stroke, fill};
                this->circles.insert({obj_label, circle});
                this->_visitor->visit_object_draw(circle);
                break;
            }
        case Object::Type::ELLIPSIS: {
                auto stroke = obj_node["stroke"].as<Object::Stroke<RGBColor>>();
                auto radiusX = obj_node["radius_v"].as<double>();
                auto radiusY = obj_node["radius_h"].as<double>();
                auto center = find_point(obj_node["center"]).value();//obj_node["center"].as<Point2D<double>>();
                auto fill = obj_node["fill"]
                    ? std::make_optional(obj_node["fill"].as<Object::Fill<RGBColor>>()) 
                    : std::nullopt;
                Ellipsis<> ellipsis {center, {radiusX, radiusY}, stroke, fill};
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
                    try {
                        vertices.push_back(it->as<Point2D<double>>());
                    } catch(const YAML::BadConversion& e) {
                        std::string pointname = it->as<std::string>();
                        if (auto point_it = points.find(pointname); point_it != points.end()) {
                            vertices.push_back(point_it->second.coords()); 
                        }
                    }
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
                    if (fill != std::nullopt and fill.value().filler == Object::Filler::SCANLINE) {
                        polygons_scanline.insert({obj_label, poly}); 
                    }
                    this->polygons.insert({obj_label, poly});
                    this->_visitor->visit_object_draw(poly);
                }
                break;
            }
        default:
            throw new std::logic_error("invalid object type");
    }
}

std::optional<Point2D<double>> YAMLSceneDescReader::find_point(const YAML::Node& node) {
    Point2D<double> p;
    try {
        return node.as<Point2D<double>>();
    } catch (const YAML::BadConversion& e) {
        if (auto point_it = points.find(node.as<std::string>()); point_it != points.end())
            return point_it->second.coords();
        return std::nullopt;
    }
}
