#include <iostream>
#include <variant>
#include "canvas/reader/YAMLSceneDescReader.h"
#include "canvas/Canvas2D.h"
#include "printer/NetpbmPrinter.h"
#include "drawers/DDALineDrawer.h"
#include "drawers/PointDrawer.h"
#include "objects/LineSegment.h"
#include "objects/Point.h"

int main(void) {

    //YAMLSceneDescReader reader;
    //reader.read("/home/vitorgreati/git-repos/raster/examples/basic-scene.yml");
    
    Canvas2D<3> canvas {50,50};

/*    for (int i = 10; i < 30; ++i) {
      for (int j = 10; j < 30; ++j) {
          canvas.set({i, j}, {255,0,0}); 
      }
    }

    for (int i = 70; i < 90; ++i) {
      for (int j = 70; j < 90; ++j) {
          canvas.set({i, j}, {0,255,0}); 
      }
    }
*/
    auto [r, g, b] = canvas.at({1,1});

    NetpbmPrinter<unsigned char> printer;

    Configs<NetpbmParams> configs {{
        {NetpbmParams::IMAGE_WIDTH, canvas.width()},
        {NetpbmParams::IMAGE_HEIGHT, canvas.height()}, 
        {NetpbmParams::IMAGE_CHANNELS, canvas.channels()},
        {NetpbmParams::PBM_TYPE, (int) NetpbmType::PIX_MAP}, 
        {NetpbmParams::PBM_ENCODING, (int) NetpbmEncoding::ASCII},
        {NetpbmParams::MAX_INTENSITY, 255}
    }};
    

    DDALineDrawer line_drawer {canvas};
    line_drawer.draw(LineSegment<double>{{10,10}, {1, 1}, {255, 255, 255}});
    line_drawer.draw(LineSegment<double>{{10,10}, {1, 19}, {255, 255, 255}});
    line_drawer.draw(LineSegment<double>{{1,15}, {10, 10}, {255, 255, 255}});
    line_drawer.draw(LineSegment<double>{{0,1}, {19, 10}, {0, 255, 0}});

    PointDrawer point_drawer {canvas};
    Point<> point {{2, 2}, {0, 255, 0}};
    point_drawer.draw(point);

    printer.print(canvas.data(), configs, "../build/testimage.ppm"); 

    return 0;
}
