//
// Created by Erdınc Kaya on 2018-12-21.
//

#ifndef INANNA_SCROLLVIEWER_H
#define INANNA_SCROLLVIEWER_H

#include "../Types.h"

namespace Inanna {
    struct ScrollViewer {
        explicit ScrollViewer(const DirectionType &direction) : direction(direction) {}

        DirectionType direction;
    };
}

#endif //INANNA_SCROLLVIEWER_H
