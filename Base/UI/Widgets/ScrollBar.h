//
// Created by Erdınc Kaya on 2018-12-27.
//

#ifndef INANNA_SCROLLBAR_H
#define INANNA_SCROLLBAR_H


#include "../Types.h"

namespace Inanna {
    struct ScrollBar {
        explicit ScrollBar(const DirectionType &direction) : direction(direction), value(Vecf(0, 0)),
                                                             ratio(Vecf(0, 0)) {}

        DirectionType direction;

        Vecf value;
        Vecf ratio;
    };
}

#endif //INANNA_SCROLLBAR_H
