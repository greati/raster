#ifndef __IMGPROC_UTILS__
#define __IMGPROC_UTILS__

#include "common.h"
#include "canvas/Canvas2D.h"
#include <algorithm>

namespace raster {

    void convolve(const Canvas<Point2D<int>, 3> & canvas, const Matrix<float> convmatrix, 
            Point2D<int> from, Point2D<int> to);

};

#endif
