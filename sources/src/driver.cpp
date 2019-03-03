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

int main(void) {

    Canvas2D<3> canvas {200,200};

    YAMLSceneDescReader reader {std::make_unique<CanvasDescVisitor>(canvas)};
    reader.read("/home/vitorgreati/git-repos/raster/examples/polygons/polygons.yml");

    NetpbmPrinter<unsigned char> printer;

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
