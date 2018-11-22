//
// Created by Erdınc Kaya on 22.11.2018.
//

#ifndef INANNA_ADDCHILD_H
#define INANNA_ADDCHILD_H


#include <vector>
#include "Widget.h"

namespace Inanna {

    struct ChildInput {
        explicit ChildInput() = default;

        explicit ChildInput(const entityx::Entity* parent, const entityx::Entity* child, bool add) : parent(parent), child(child),
                                                                                       add(add) {}

        const entityx::Entity* parent;
        const entityx::Entity* child;
        bool add{};
    };
}

#endif //INANNA_ADDCHILD_H
