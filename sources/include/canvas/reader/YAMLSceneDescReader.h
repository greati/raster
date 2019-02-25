#ifndef __YAMLSCENEREADER__
#define __YAMLSCENEREADER__

#include <string>
#include "canvas/reader/SceneDescReader.h"
#include "yaml-cpp/yaml.h"
#include "canvas/reader/DescVisitor.h"

/**
 * Reader for scenes described in YAML.
 * */
class YAMLSceneDescReader : public SceneDescReader {

    private:
       std::unique_ptr<DescVisitor> visitor;

    public:

       void read(const std::string & filename) const override;

    protected:

       void process_scene(const YAML::Node & scene_node) const;
       void process_object(const YAML::Node & obj_node) const;
};

#endif
