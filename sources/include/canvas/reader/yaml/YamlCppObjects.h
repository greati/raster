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

}


#endif
