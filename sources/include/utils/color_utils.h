#ifndef __COLOR_UTILS__
#define __COLOR_UTILS__

#include "common.h"

namespace raster {

    /**
     * Convert from RGB to HSV.
     *
     * */
    HSVColor rgb_to_hsv(const RGBColor & rgb);

    /**
     * Convert from HSV to RGB.
     *
     * */
    RGBColor hsv_to_rgb(const HSVColor & hsv);

    /**
     * Apply brightness to RGB color.
     *
     * */
    RGBColor apply_brightness_rgb(const RGBColor & rgb, float brightness);

    RGBColor blend_rgbs(const RGBColor & rgb1, const RGBColor & rgb2);

};

#endif
