#ifndef __YAMLCPPOBJS__
#define __YAMLCPPOBJS__

#include "yaml-cpp/yaml.h"

namespace YAML {
       template<>
       struct convert<Point2D<double>> {
            static Node encode(const Point2D<double>& rhs) {
                Node node;
                return node;
            }
            static bool decode(const Node& node, Point2D<double> & point2d) {
                if (!node.IsSequence() || node.size() != 2)
                    return false;
                point2d.first = node[0].as<double>(); 
                point2d.second = node[1].as<double>(); 
                return true;
            }
       };

       template<>
       struct convert<Point2D<int>> {
            static Node encode(const Point2D<int>& rhs) {
                Node node;
                return node;
            }
            static bool decode(const Node& node, Point2D<int> & point2d) {
                if (!node.IsSequence() || node.size() != 2)
                    return false;
                point2d.first = node[0].as<int>(); 
                point2d.second = node[1].as<int>(); 
                return true;
            }
       };

       template<>
       struct convert<RGBColor> {
            static Node encode(const RGBColor& rhs) {
                Node node;
                return node;
            }
            static bool decode(const Node& node, RGBColor & rgbColor) {
                if (!node.IsSequence() || node.size() != 3)
                    return false;
                std::get<0>(rgbColor) = node[0].as<int>(); 
                std::get<1>(rgbColor) = node[1].as<int>(); 
                std::get<2>(rgbColor) = node[2].as<int>(); 
                return true;
            }
       };

       template<>
       struct convert<Object::Stroke<RGBColor>> {
            static Node encode(const Object::Stroke<RGBColor>& rhs) {
                Node node;
                return node;
            }
            static bool decode(const Node& node, Object::Stroke<RGBColor> & stroke) {
                stroke.color = node["color"].as<RGBColor>();
                if (node["thickness"])
                    stroke.thickness = node["thickness"].as<int>();
                if (node["drawer"])
                    stroke.drawer = node["drawer"].as<Object::StrokeDrawer>();
                if (node["antialiased"])
                    stroke.antialiased = node["antialiased"].as<bool>();
                return true;
            }
       };

       template<>
       struct convert<Object::Fill<RGBColor>> {
            static Node encode(const Object::Fill<RGBColor>& rhs) {
                Node node;
                return node;
            }
            static bool decode(const Node& node, Object::Fill<RGBColor> & fill) {
                fill.color = node["color"].as<RGBColor>();
                if (node["filler"])
                    fill.filler = node["filler"].as<Object::Filler>();
                if (node["seed"])
                    fill.seed = node["seed"].as<Point2D<int>>();
                return true;
            }
       };

       template<>
       struct convert<Object::Type> {
            static Node encode(const Object::Type& rhs) {
                Node node;
                return node;
            }
            static bool decode(const Node& node, Object::Type & objtype) {
                auto type = node["type"].as<std::string>();
                if (type == "point")
                    objtype = Object::Type::POINT;
                else if (type == "line")
                    objtype = Object::Type::LINE_SEGMENT;
                else if (type == "circle")
                    objtype = Object::Type::CIRCLE;
                else if (type == "polyline")
                    objtype = Object::Type::POLYLINE;
                else if (type == "polygon")
                    objtype = Object::Type::POLYGON;
                else if (type == "ellipsis")
                    objtype = Object::Type::ELLIPSIS;
                else
                    return false;
                return true;
            }
       };

       template<>
       struct convert<Object::Filler> {
            static Node encode(const Object::Filler& rhs) {
                Node node;
                return node;
            }
            static bool decode(const Node& node, Object::Filler & objtype) {
                auto type = node.as<std::string>();
                if (type == "scanline")
                    objtype = Object::Filler::SCANLINE;
                else if (type == "flood")
                    objtype = Object::Filler::FLOOD;
                else if (type == "boundary")
                    objtype = Object::Filler::BOUNDARY;
                else 
                    return false;
                return true;
            }
       };

       template<>
       struct convert<Object::StrokeDrawer> {
            static Node encode(const Object::StrokeDrawer& rhs) {
                Node node;
                return node;
            }
            static bool decode(const Node& node, Object::StrokeDrawer & objtype) {
                auto type = node.as<std::string>();
                if (type == "bresenham")
                    objtype = Object::StrokeDrawer::BRESENHAM;
                else if (type == "dda")
                    objtype = Object::StrokeDrawer::DDA;
                else if (type == "wu")
                    objtype = Object::StrokeDrawer::WU;
                else 
                    return false;
                return true;
            }
       };

}


#endif
