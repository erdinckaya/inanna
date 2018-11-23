//
// Created by Erdınc Kaya on 22.11.2018.
//

#ifndef INANNA_POSITION_H
#define INANNA_POSITION_H

#include "../../Util/Math/Vec2.h"

namespace Inanna {
    struct Position {
        explicit Position(const Vecf &position = Vecf(0, 0), const Vecf &global = Vecf(0, 0)) : position(position),
                                                                                                global(global) {}

        Vecf position;
        Vecf global;
    };
}
#endif //INANNA_POSITION_H
