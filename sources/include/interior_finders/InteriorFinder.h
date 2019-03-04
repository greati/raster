#ifndef __INTERIORFINDER__
#define __INTERIORFINDER__

#include "common.h"

template<typename ObjType, typename PointType=Point2D<int>>
class InteriorFinder {

    public:

        virtual PointType find_one(const ObjType & obj) const = 0;
        virtual std::vector<PointType> find_many(const ObjType & obj) const = 0;

};

#endif
