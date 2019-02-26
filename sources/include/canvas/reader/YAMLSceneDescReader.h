#ifndef __YAMLSCENEREADER__
#define __YAMLSCENEREADER__

#include <string>
#include "canvas/reader/SceneDescReader.h"
#include "canvas/reader/DescVisitor.h"
#include <memory>
#include "yaml-cpp/yaml.h"

/**
 * Reader for scenes described in YAML.
 * */
class YAMLSceneDescReader : public SceneDescReader {

    private:
       std::unique_ptr<DescVisitor> _visitor;

    public:

       YAMLSceneDescReader(std::unique_ptr<DescVisitor> visitor) : _visitor {std::move(visitor)} {}

       void read(const std::string & filename) const override;

    protected:

       void process_scene(const YAML::Node & scene_node) const;
       void process_object(const YAML::Node & obj_node) const;
};

#endif
