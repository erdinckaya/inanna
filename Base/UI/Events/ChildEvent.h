//
// Created by Erdınc Kaya on 22.11.2018.
//

#ifndef INANNA_ADDCHILD_H
#define INANNA_ADDCHILD_H


#include <vector>
#include "../Components/Widget.h"

namespace Inanna {

    namespace ex = entityx;

    struct ChildEvent {
        ChildEvent(ex::Entity parent, ex::Entity child, bool add) : parent(parent), child(child), add(add) {}

        ex::Entity parent, child;
        bool add;
    };
}

#endif //INANNA_ADDCHILD_H
