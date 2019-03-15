#ifndef __INTERIORFINDER__
#define __INTERIORFINDER__

#include "common.h"

/**
 * Find interior points to an object.
 *
 * @author Vitor Greati
 * */
template<typename ObjType, typename PointType=Point2D<int>>
class InteriorFinder {

    public:
        
        /**
         * Find one point.
         *
         * @param obj the object
         * @return a point
         * */
        virtual PointType find_one(const ObjType & obj) const = 0;

        /**
         * Find a list of interior points.
         *
         * @param obj the object
         * @return list of points
         * */
        virtual std::vector<PointType> find_many(const ObjType & obj) const = 0;

};

#endif
