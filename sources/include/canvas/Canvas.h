#ifndef __CANVAS__
#define __CANVAS__

/**
 * A canvas for drawing scenes.
 *
 * @author Vitor Greati
 */
class Canvas {

    private:
        int nchannels;                              /* Number of channels */
        int width;                                  /* Canvas width */
        int height;                                 /* Canvas height */
        std::unique_ptr<unsigned char> data;        /* Canvas pixels */

};

#endif
