#include <iostream>
#include <variant>
#include "canvas/reader/YAMLSceneDescReader.h"
#include "canvas/Canvas2D.h"
#include "printer/NetpbmPrinter.h"
#include "drawers/DDALineDrawer.h"
#include "drawers/BresenhamLineDrawer.h"
#include "drawers/PointDrawer.h"
#include "objects/LineSegment.h"
#include "objects/Point.h"
#include "canvas/CanvasDescVisitor.h"

int main(int argn, char* args[]) {

    Canvas2D<3> canvas {200,200};

    std::string file_path;
    if (argn < 2) {
        std::cout << "provide a description file path";
        return 0;
    }
    file_path = std::string(args[1]);

    std::string destination;
    if (argn < 3) {
        std::cout << "provide the destination path";
        return 0;
    }
    destination = std::string(args[2]);


    YAMLSceneDescReader reader {std::make_unique<CanvasDescVisitor>(canvas)};
    reader.read(file_path);

    NetpbmPrinter<unsigned char> printer;

    Configs<NetpbmParams> configs {{
        {NetpbmParams::IMAGE_WIDTH, canvas.width()},
        {NetpbmParams::IMAGE_HEIGHT, canvas.height()}, 
        {NetpbmParams::IMAGE_CHANNELS, canvas.channels()},
        {NetpbmParams::PBM_TYPE, (int) NetpbmType::PIX_MAP}, 
        {NetpbmParams::PBM_ENCODING, (int) NetpbmEncoding::ASCII},
        {NetpbmParams::MAX_INTENSITY, 255}
    }};

    printer.print(canvas.data(), configs, destination); 

    return 0;
}
