#ifndef __COMMON__
#define __COMMON__

#include <array>
#include <tuple>

template<typename T>
using Point2D = std::pair<T, T>;

template<int N>
using Size = std::array<int, N>;

using RGBColor = std::tuple<unsigned char, unsigned char, unsigned char>;
using HSVColor = std::tuple<float, float, float>;

template<int NChannels>
using PixelValue = std::array<unsigned char, NChannels>;

#endif
