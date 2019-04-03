//
// Created by Erdınc Kaya on 2019-04-03.
//

#ifndef INANNA_VELOCITY_H
#define INANNA_VELOCITY_H

#include "../../Util/Math/Vec2.h"

namespace Inanna {
    struct Velocity {
        explicit Velocity(const Vecf &value = Vecf(0, 0)) : value(value) {}

        Vecf value;

        REFLECT()
    };
}

#endif //INANNA_VELOCITY_H
