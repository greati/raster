#include <iostream>
#include "canvas/reader/YAMLSceneDescReader.h"
#include "canvas/Canvas2D.h"

int main(void) {

    //YAMLSceneDescReader reader;
    //reader.read("/home/vitorgreati/git-repos/raster/examples/basic-scene.yml");
    
    Canvas2D<3> canvas {800, 600};

    canvas.set({0,0}, {20,30,10});
    auto [r, g, b] = canvas.at({0,0});
    std::cout << (int) r << " " << (int) g << " " << (int) b << std::endl;
    
    return 0;
}
