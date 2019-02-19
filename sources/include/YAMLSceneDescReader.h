#ifndef __YAMLSCENEREADER__
#define __YAMLSCENEREADER__

#include <string>
#include "SceneDescReader.h"
#include "yaml-cpp/yaml.h"

/**
 * Reader for scenes described in YAML.
 * */
class YAMLSceneDescReader : public SceneDescReader {

    public:

       void read(const std::string & filename);
};

#endif
