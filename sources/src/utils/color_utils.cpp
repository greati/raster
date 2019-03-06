#include "utils/color_utils.h"
#include <cmath>
#include <algorithm>

/**
 * Convert from RGB to HSV.
 *
 * */
HSVColor raster::rgb_to_hsv(const RGBColor & rgb) {

    auto [r, g, b] = rgb;

    float rf = 1./255 * r;
    float gf = 1./255 * g;
    float bf = 1./255 * b;

    float max = std::max({rf, gf, bf});
    float min = std::min({rf, gf, bf});

    // compute H
    float h = 0;
    if (rf == max and gf >= bf)
        h = 60 * (gf - bf) / (max - min) + 0;
    else if (rf == max and gf < bf)
        h = 60 * (gf - bf)/ (max - min) + 360;
    else if (gf == max)
        h = 60 * (bf - rf) / (max - min) + 120; 
    else if (bf == max)
        h = 60 * (rf - gf) / (max - min) + 240;
    // compute S
    float s = (max - min) / max;
    // compute V
    float v = max;

    return HSVColor{h, s, v};
}

/**
 * Convert from HSV to RGB.
 *
 * */
RGBColor raster::hsv_to_rgb(const HSVColor & hsv) {

    auto [h, s, v] = hsv;

    auto to255 = [](float rf, float gf, float bf) {
        return RGBColor{rf*255, gf*255, bf*255}; 
    };

    if (s == 0)
        return to255(v, v, v);

    auto Hi = static_cast<int>(std::floor(h / 60.0)) % 6;
    auto f = h/60 - Hi;
    auto p = v * (1 - s);
    auto q = v * (1 - f * s);
    auto t = v * (1 - (1 - f) * s);

    switch(Hi) {
        case 0: return to255(v, t, p);
        case 1: return to255(q, v, p);
        case 2: return to255(p, v, t);
        case 3: return to255(p, q, v);
        case 4: return to255(t, p, v);
        case 5: return to255(v, p, q);
        default: return to255(1, 1, 1);
    }
}

/**
 * Apply brightness to RGB color.
 *
 * */
RGBColor raster::apply_brightness_rgb(const RGBColor & rgb, float brightness) {
    if (brightness < 0.0 || brightness > 1.0) {
        throw std::invalid_argument("brightness must be in the [0.0, 1.0] range");
    }
    auto [h, s, v] = rgb_to_hsv(rgb);
    return hsv_to_rgb({h, s, brightness});
}
