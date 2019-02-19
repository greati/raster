#include <iostream>
#include "YAMLSceneDescReader.h"

void YAMLSceneDescReader::read(const std::string & filename) {
    
    YAML::Node config = YAML::LoadFile(filename);

    if (config["scene"]) {
        std::cout << "Last logged in: " << config["scene"].as<std::string>() << "\n";
    }

}
