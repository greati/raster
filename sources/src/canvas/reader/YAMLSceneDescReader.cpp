#include <iostream>
#include "lodepng.h"
#include "canvas/reader/YAMLSceneDescReader.h"
#include "canvas/reader/yaml/YamlCppObjects.h"

void YAMLSceneDescReader::read(const std::string & filename) {
    
    YAML::Node root_node = YAML::LoadFile(filename);

    if (!root_node["scene"])
        throw new std::logic_error("Parse error: missing scene top level");

    if (root_node["settings"]) {
        auto settings = root_node["settings"];
        if (settings["points"]) {
            auto points = settings["points"];
            for (auto it = points.begin(); it != points.end(); ++it) {
                auto label = it->first.as<std::string>();
                auto coords = it->second.as<Point2D<double>>();
                Point<> p {coords, {0, 0, 0}};
                this->points.insert({label, p});
            }
        }

        if (settings["colors"]) {
            auto colors = settings["colors"];
            for (auto it = colors.begin(); it != colors.end(); ++it) {
                auto label = it->first.as<std::string>();
                auto color = it->second.as<RGBColor>();
                SceneSettings::color_pallete.insert({label, color});
            }
        }

        if (settings["fills"]) {
            auto fills = settings["fills"];
            for (auto it = fills.begin(); it != fills.end(); ++it) {
                auto label = it->first.as<std::string>();
                auto fill = it->second.as<Object::Fill<>>();
                SceneSettings::fill_pallete.insert({label, fill});
            }
        }

        if (settings["strokes"]) {
            auto strokes = settings["strokes"];
            for (auto it = strokes.begin(); it != strokes.end(); ++it) {
                auto label = it->first.as<std::string>();
                auto stroke = it->second.as<Object::Stroke<>>();
                SceneSettings::stroke_pallete.insert({label, stroke});
            }
        }
    }

    auto scene = root_node["scene"];

    if (scene["width"] && scene["height"]) {
        this->_visitor->visit_scene_size(Size<2>{scene["height"].as<int>(), scene["width"].as<int>()});
    } else throw std::logic_error("provide the scene size in terms of height and width");

    if (scene["background"]) {
        auto bgcolor = get_color(scene["background"]);
        if (bgcolor == std::nullopt) {
            std::string file_path = scene["background"].as<std::string>();
            this->_visitor->visit_scene_background(file_path);
        } else {
            this->_visitor->visit_scene_background(bgcolor.value());
        }
    }

    if (scene["global_aa"]) {
        this->_visitor->visit_scene_global_aa(scene["global_aa"].as<bool>()); 
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
                assert_node(obj_node["coords"], "coords");
                assert_node(obj_node["color"], "color");
                auto coords = find_point(obj_node["coords"]).value();
                auto color = get_color(obj_node["color"]).value();
                Point<> p {coords, color};
                this->points.insert({obj_label, p});
                this->_visitor->visit_object_draw(p);
                break;
            }
        case Object::Type::LINE_SEGMENT: {
                assert_node(obj_node["start"], "start");
                assert_node(obj_node["end"], "end");
                assert_node(obj_node["stroke"], "stroke");
                Point2D<double> start = find_point(obj_node["start"]).value();
                Point2D<double> end = find_point(obj_node["end"]).value();
                auto stroke = get_stroke(obj_node["stroke"]).value();
                LineSegment line {start, end, stroke};
                this->line_segments.insert({obj_label, line});
                this->_visitor->visit_object_draw(line);
                break;
            }
        case Object::Type::CIRCLE: {
                assert_node(obj_node["stroke"], "stroke");
                assert_node(obj_node["radius"], "radius");
                assert_node(obj_node["center"], "center");
                auto stroke = get_stroke(obj_node["stroke"]).value();
                auto radius = obj_node["radius"].as<double>();
                auto center = find_point(obj_node["center"]).value();
                std::optional<std::pair<float, float>> arc = std::nullopt;
                if (obj_node["arc"])
                     arc = {obj_node["arc"][0].as<double>(), obj_node["arc"][1].as<double>()};  
                std::optional<Object::Fill<>> fill = std::nullopt;
                if (obj_node["fill"])
                    fill = get_fill(obj_node["fill"]);
                Circle circle {center, radius, stroke, fill, arc};
                this->circles.insert({obj_label, circle});
                this->_visitor->visit_object_draw(circle);
                break;
            }
        case Object::Type::ELLIPSIS: {
                assert_node(obj_node["stroke"], "stroke");
                assert_node(obj_node["radius_v"], "radius_v");
                assert_node(obj_node["radius_h"], "radius_h");
                assert_node(obj_node["center"], "center");
                auto stroke = get_stroke(obj_node["stroke"]).value();
                auto radiusX = obj_node["radius_v"].as<double>();
                auto radiusY = obj_node["radius_h"].as<double>();
                auto center = find_point(obj_node["center"]).value();
                auto fill = get_fill(obj_node["fill"]);
                std::optional<std::pair<float, float>> arc = std::nullopt;
                if (obj_node["arc"])
                     arc = {obj_node["arc"][0].as<double>(), obj_node["arc"][1].as<double>()};  
                Ellipsis<> ellipsis {center, {radiusX, radiusY}, stroke, fill, arc};
                this->ellipsis.insert({obj_label, ellipsis});
                this->_visitor->visit_object_draw(ellipsis);
                break;
            }
        case Object::Type::POLYLINE:
        case Object::Type::POLYGON: {
                assert_node(obj_node["stroke"], "stroke");
                assert_node(obj_node["vertices"], "vertices");
                auto stroke = get_stroke(obj_node["stroke"]);
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
                    auto interior_points = 
                        obj_node["interior"] ? std::make_optional<std::vector<Point2D<int>>>() : std::nullopt;
                    if (interior_points != std::nullopt) {
                        for (auto it = obj_node["interior"].begin(); it != obj_node["interior"].end(); ++it) {
                            interior_points.value().push_back(it->as<Point2D<int>>());
                        }
                    }
                    auto fill = get_fill(obj_node["fill"]);
                    Polygon poly {vertices, stroke, fill, interior_points};
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

std::optional<RGBColor> YAMLSceneDescReader::get_color(const YAML::Node& node) {
    try {
        return node.as<RGBColor>();
    } catch (const YAML::BadConversion& e) {
        if (auto point_it = SceneSettings::color_pallete.find(node.as<std::string>()); point_it != SceneSettings::color_pallete.end())
            return point_it->second;
        return std::nullopt;
    }
}

std::optional<Object::Fill<>> YAMLSceneDescReader::get_fill(const YAML::Node& node) {
    if (!node) return std::nullopt;
    try {
        return node.as<Object::Fill<>>();
    } catch (const YAML::BadConversion& e) {
        if (auto point_it = SceneSettings::fill_pallete.find(node.as<std::string>()); point_it != SceneSettings::fill_pallete.end())
            return point_it->second;
        return std::nullopt;
    }
}

std::optional<Object::Stroke<>> YAMLSceneDescReader::get_stroke(const YAML::Node& node) {
    try {
        return node.as<Object::Stroke<>>();
    } catch (const YAML::BadConversion& e) {
        if (auto point_it = SceneSettings::stroke_pallete.find(node.as<std::string>()); point_it != SceneSettings::stroke_pallete.end())
            return point_it->second;
        return std::nullopt;
    }
}

