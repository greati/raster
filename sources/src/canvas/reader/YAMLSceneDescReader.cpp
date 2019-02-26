#include <iostream>
#include "canvas/reader/YAMLSceneDescReader.h"

void YAMLSceneDescReader::read(const std::string & filename) const {
    
    YAML::Node root_node = YAML::LoadFile(filename);

    if (!root_node["scene"])
        throw new std::logic_error("Parse error: missing scene top level");

    auto scene = root_node["scene"];

    if (scene["background"])
        this->_visitor->visit_scene_background("hi");
}
