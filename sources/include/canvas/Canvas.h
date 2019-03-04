#ifndef __CANVAS__
#define __CANVAS__

#include "common.h"
#include <new>

template<typename CoordType, int NChannels = 3>
class Canvas {

    public:

        virtual void set(CoordType point, PixelValue<NChannels> value) const = 0;

        virtual void set(CoordType point, PixelValue<NChannels> value, std::nothrow_t) const noexcept = 0;

        virtual int height() const = 0;

        virtual int width() const = 0;

        virtual PixelValue<NChannels> at(CoordType point) const = 0;
};

#endif
