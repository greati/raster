#ifndef __DRAWER__
#define __DRAWER__

#include <vector>
#include <memory>
#include "objects/Object.h"

class Drawer {

    public:
        virtual std::vector<int> draw(std::shared_ptr<Object> obj) const = 0;

};

#endif
