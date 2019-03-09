# Raster

Raster in C++.

Features:

Objects:
* [x] Points
* [ ] Lines
    * [x] DDA (thickness 1)
    * [x] Bresenham (thickness 1)
    * [x] Wu (thickness 1)
    * [x] DDA (thickness N)
    * [ ] Bresenham (thickness N)
    * [ ] Wu (thickness N)
* [ ] Circles
    * [x] Midpoint (thickness 1)
    * [x] Midpoint (thickness N)
    * [x] Wu (thickness 1)
    * [ ] Wu (thickness N)
* [ ] Arcs
* [ ] Ellipsis
    * [x] Wu (thickness 1)
    * [ ] Wu (thickness N)
* [ ] Fills
    * [x] Polygon interior finder
    * [ ] Circle interior finder
    * [ ] Ellipsis interior finder
    * [ ] Scan-line 
    * [x] Flood fill
    * [x] Boundary fill 
* [ ] Antialiasing
    * [x] Xialing-Wu
    * [ ] Convolution

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

