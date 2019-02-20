#include <iostream>
#include "canvas/reader/YAMLSceneDescReader.h"

int main(void) {

    YAMLSceneDescReader reader;
    
    reader.read("/home/vitorgreati/git-repos/raster/examples/basic-scene.yml");

    return 0;
}
