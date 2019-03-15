# Raster

A simple 2D Raster in C++.

<img src="https://cdn1.imggmi.com/uploads/2019/3/16/8a52b068ecc89daceaf9b1a2a69ece6a-full.png"/>

## Features:

Objects:
* [x] Points
* [ ] Lines
    * [x] DDA (thickness 1)
    * [x] Bresenham (thickness 1)
    * [x] Wu (thickness 1) - experimental, working only for black backgrounds
    * [x] DDA (thickness N) - experimental, problems with vertical and horizontal
    * [ ] Bresenham (thickness N)
    * [ ] Wu (thickness N)
* [ ] Circles
    * [x] Midpoint (thickness 1)
    * [x] Midpoint (thickness N)
    * [x] Wu (thickness 1) - experimental, working only for black backgrounds
    * [ ] Wu (thickness N)
* [x] Circle arcs
    * [x] DDA (thickness 1)
    * [x] DDA (thickness N)
* [ ] Ellipsis
    * [x] Wu (thickness 1)
    * [ ] Wu (thickness N)
* [ ] Fills
    * [ ] Polygon interior finder (architecture done, but still not working)
    * [x] Circle interior finder - takes the center
    * [x] Ellipsis interior finder - takes the center
    * [x] Polygon scan-line
    * [x] Flood fill
    * [x] Boundary fill
* [ ] Antialiasing
    * [x] Xialing-Wu - experimental, only for black backgrounds
    * [x] Convolution

## Build

```
mkdir build
cd build
cmake ../sources .
cmake --build .
```

## Test

```
make test
```

