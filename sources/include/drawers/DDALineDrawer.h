#ifndef __DDALINEDRAWER__
#define __DDALINEDRAWER__

#include "drawers/Drawer.h"
#include "objects/Object.h"

class DDALineDrawer : public Drawer {

    public:
        std::vector<int> draw(std::shared_ptr<Object> obj) const override {
            return {};
        };

};

#endif
