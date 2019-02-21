#ifndef __CANVAS__
#define __CANVAS__

#include "common.h"

template<typename CoordType, int NChannels = 3>
class Canvas {

    public:

        virtual void set(CoordType point, PixelValue<NChannels> value) const = 0;
};

#endif
