#include "canvas/Canvas2D.h"

template<int N>
typename Canvas2D<N>::Value Canvas2D<N>::at(Canvas2D<N>::Point2D point) const {
    auto [start, end] = real_pos(point);
    Canvas2D<N>::Value v;
    for (auto i = start, j = 0; i < end; ++i, ++j)
        v[j] = _data[i];
    return v;
}

template<int N>
void Canvas2D<N>::set(Canvas2D<N>::Point2D point, Canvas2D<N>::Value value) const {
    auto [start, end] = real_pos(point);
    for (auto i = start, j = 0; i < end; ++i, ++j)
        _data[i] = value[j];
}

template<int N>
std::pair<int, int> Canvas2D<N>::real_pos(const Canvas2D<N>::Point2D & point) const {
    validate(point);
    auto [i, j] = point;
    auto start = i*_width*N + j*N;
    return {start, start + N};
}

template<int N>
Canvas2D<N>::Canvas2D(int width, int height) : _width{width}, _height{height} {
    this->_data = std::make_unique<unsigned char[]>(width * height * N);
}

template<int N>
void Canvas2D<N>::validate(const Canvas2D<N>::Point2D & point) const {
    auto [x, y] = point;

    if (x < 0 || x >= _width)
        throw std::invalid_argument("point outsite the width range, " + std::to_string(x));
    if (y < 0 || y >= _height)
        throw std::invalid_argument("point outsite the height range, " + std::to_string(y));
}

template class Canvas2D<3>;
