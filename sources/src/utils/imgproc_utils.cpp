#include "utils/imgproc_utils.h"

void raster::convolve(const Canvas<Point2D<int>, 3> & canvas, const Matrix<float> kernel, 
            Point2D<int> from, Point2D<int> to) {


    if (from.first > to.first) {
        std::swap(from, to);
    }

    auto kernel_size = kernel.size();

    for (int i = from.first; i <= to.first; ++i) { // lines
        for (int j = from.second; j <= to.second; j++) { //cols
            
            float val[3] = {0.0, 0.0, 0.0};

            for (int ic = 0; ic < kernel_size; ++ic) { //lines
                for (int jc = 0; jc < kernel_size; ++jc) { //cols

                    std::array<unsigned char, 3> pixel = {0, 0, 0};

                    if (not (i+ic < 0 || i+ic >= canvas.height() || j+jc < 0 || j+jc >= canvas.width()))
                        pixel = canvas.at({i+ic, j+jc});

                    val[0] += pixel[0] * kernel[ic][jc];
                    val[1] += pixel[1] * kernel[ic][jc];
                    val[2] += pixel[2] * kernel[ic][jc];
                }
            }

            canvas.set({i, j}, {(unsigned char) val[0], (unsigned char) val[1], (unsigned char) val[2]});

        }
    }

}
