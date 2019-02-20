#include <iostream>
#include <variant>
#include "canvas/reader/YAMLSceneDescReader.h"
#include "canvas/Canvas2D.h"
#include "printer/NetpbmPrinter.h"

int main(void) {

    //YAMLSceneDescReader reader;
    //reader.read("/home/vitorgreati/git-repos/raster/examples/basic-scene.yml");
    
    Canvas2D<3> canvas {100,100};

    canvas.set({0,0}, {20,30,10});
    
    for (int i = 20; i < 40; ++i) {
        for (int j = 20; j < 40; ++j) {
            canvas.set({i, j}, {255,0,0}); 
        }
    }

    auto [r, g, b] = canvas.at({20,39});
    std::cout << (int) r << std::endl;

    NetpbmPrinter<unsigned char[]> printer;

    Configs<NetpbmParams> configs {{
        {NetpbmParams::IMAGE_WIDTH, canvas.width()},
        {NetpbmParams::IMAGE_HEIGHT, canvas.height()}, 
        {NetpbmParams::IMAGE_CHANNELS, canvas.channels()},
        {NetpbmParams::PBM_TYPE, (int) NetpbmType::PIX_MAP}, 
        {NetpbmParams::PBM_ENCODING, (int) NetpbmEncoding::ASCII},
        {NetpbmParams::MAX_INTENSITY, 255}
    }};
    
    printer.print(canvas.data(), configs, "../build/testimage.ppm"); 

    return 0;
}
